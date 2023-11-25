#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12
#include "./Includes/ray.h"
#include "./Includes/color.h"
#include <cmath>
#include "float.h"

#define M_PI 3.14159265358979323846 

// cores basicas para testes com objetos
const color red(1.0f,0.0f,0.0f);
const color green(0.0f,1.0f,0.0f);
const color blue(0.0f,0.0f,1.0f);

struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    color cor;
};

class hitable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

class sphere: public hitable {
    public:
        sphere() {}
        sphere(glm::vec3 cen, float r, color c) : center(cen), radius(r), cor(c) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        glm::vec3 center;
        float radius;
        color cor;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.location() - center; // vetor que vai do centro da esfera até a origem do raio
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius; // calcula o dot product de oc com ele mesmo, e subtrai o raio ao quadrado
    //a, b e c são os coeficientes da equação de segundo grau
    float discriminant = b*b - a*c;
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.cor = cor;
            return true;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.cor = cor;
            return true;
        }
    }
    
    return false;
}

class hitable_list: public hitable {
    public:
        hitable_list() {}
        hitable_list(hitable **l, int n) { list = l; list_size = n;}
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        hitable **list;
        int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    double closet_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        if(list[i]->hit(r, t_min, closet_so_far, temp_rec)) {
            hit_anything = true;
            closet_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

class plane: public hitable {
    public:
        plane() {}
        plane(glm::vec3 p, glm::vec3 n, color c) : plane_point(p), normal(normalize(n)), cor(c) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        glm::vec3 plane_point;
        glm::vec3 normal;
        color cor;
};

bool plane::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    float t = glm::dot((plane_point - r.location()), normal) / glm::dot(r.direction(), normal);

    if(t < t_max && t > t_min){
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = normal;
        rec.cor = cor;
        return true;
    }
    return false;
}

// função que define a cor que será exibida
color ray_color(const ray& r, hitable *world)
{
    hit_record rec;
    if(world->hit(r, 0.0f, FLT_MAX, rec)){
        //return 0.5f*glm::vec3(rec.normal.x+1, rec.normal.y+1, rec.normal.z+1);
        //return red;
        return rec.cor;
    }

    color backgroundColor = glm::vec3(0.0,0.0,0.0); // cor preta pro background

    return backgroundColor;
}


/*
int hitableArraySize(hitable **array) {
    // hitable *size = array[0];
    int tamanhoArray = sizeof(array) / sizeof(array[0]);

    return tamanhoArray;
}*/

class camera {
    public:
    //camera() {}
    camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vres, float  hres, float dist);

    ray get_ray(float s, float t);

    glm::vec3 origem;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
    glm::vec3 u, v, w;
};

camera::camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vres, float  hres, float dist)
{
    w = glm::normalize(lookfrom - lookat);
    u = glm::normalize(glm::cross(vup,w));
    v = glm::cross(w,u);
    
    origem = lookfrom;
    float proporcao = vres / hres;
    
    // tamanho da largura e altura
    float xsize = 4.0f;
    float ysize = xsize * proporcao;
    
    // metades das proporcoes
    float mLargura = xsize / 2;
    float mAltura = mLargura * proporcao; 
    
    float cameraDistance = dist;

    //lower_left_corner = glm::vec3(-mLargura, -mAltura, -cameraDistance);
    lower_left_corner = origem - (mLargura*u) -(mAltura*v) - w;

    horizontal = 2*mLargura*u;
    vertical = 2*mAltura*v;
    
}

ray camera::get_ray(float s, float t)
{
    return ray(origem, lower_left_corner + s*horizontal + t*vertical - origem);
}

int main() {

    // largura e altura da tela respectivamente // resolução
    int nx = 500; // hres
    int ny = 500;  // vres

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // localização
    glm::vec3 origin(0.0f, 0.0f, 0.0f);

    // para onde a camera esta olhando
    glm::vec3 lookingat(0.0f, 0.0f, -1.0f);

    // vup
    glm::vec3 vup(0.0f, 1.0f, 0.0f);

    // distancia da camera pra tela pra tela
    float distance = 1.0f;

    // lista de objetos
    hitable *list[3];
    list[0] = new sphere(glm::vec3(2.0, 0.0, -5.0), 0.5f, red);
    list[1] = new plane(glm::vec3(0.0, 0.0, -40.0), glm::vec3(0.0, -20.0, 1.0), green);
    list[2] = new sphere(glm::vec3(0, -2.0, -5.0), 1, blue);
    //list[3] = new sphere(glm::vec3(-1.5, 0, -5), 0.5f, blue + green);
    
    hitable *world = new hitable_list(list, std::size(list));

    camera *cam = new camera(origin, lookingat, vup, ny, nx, distance);

    //std::cout << cam->lower_left_corner.x << " " << cam->lower_left_corner.y << " " << cam->lower_left_corner.z << "\n"; 
    //std::cout << cam->w.x << " " << cam->w.y << " " << cam->w.z << "\n"; 
    //std::cout << cam->u.x << " " << cam->u.y << " " << cam->u.z << "\n"; 
    //std::cout << cam->v.x << " " << cam->v.y << " " << cam->v.z << "\n"; 

    // printando os pixels
    for(int j = ny-1; j >= 0 ; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j)/ float(ny);
            ray r = cam->get_ray(u,v);

            glm::vec3 p = r.point_at_parameter(2.0f);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }


    return 0;
}
