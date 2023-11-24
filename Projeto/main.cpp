#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12
#include "./Includes/ray.h"
#include "./Includes/color.h"
#include <cmath>
#include "float.h"

#define M_PI 3.14159265358979323846 

// cores basicas para testes com objetos
const color red = glm::vec3(255.99,0.0,0.0);
const color green = glm::vec3(0.0,255.99,0.0);
const color blue = glm::vec3(0.0,0.0,255.99);

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


/*
class camera {
    public:
    camera (float vfov, float aspect);
    ray get_ray(float u, float v);
    glm::vec3 origem;
    glm::vec3 lower_left_corner;
    glm::vec3 horizontal;
    glm::vec3 vertical;
}

camera::camera(float vfov, float aspect)
{
    float teta = vfov*M_PI/180;
    float mAltura = tan(teta/2);
    float mLargura = aspect * mAltura;
    lower_left_corner = glm::vec3(-mLargura, -mAltura, -1.0);
    horizontal = glm::vec3(2*mLargura, 0.0, 0.0);
    vertical = glm::vec3(0.0, 2*mAltura, 0.0);
    origem = glm::vec3(0.0, 0.0, 0.0);
}

ray camera::get_ray(float u, float v)
{
    return ray(origem,lower_left_corner + u*horizontal + v*vertical - origem)
}
*/


int main() {

    // largura e altura da tela respectivamente // resolução
    int nx = 1000; // lres
    int ny = 500;  // hres

    // proporção da tela em uma fração
    float proportionYX = float(ny) / float(nx);

    // tamanho da tela proporcional
    float xsize = 1.0f;
    float ysize = xsize * proportionYX;

    float cameraDistance = 0.3;


    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // definindo localização da camera, e os vetores ortonormais
    // no momento tem apenas dois vetores ortonormais o horizontal e o vertical
    // o vetor horizontal deve ter o dobro do vertical visto que a largura da tela é o dobro da altura
    glm::vec3 lower_left_corner(-xsize/2, -ysize/2, -cameraDistance); // posição do canto inferior esquerdo da tela
    glm::vec3 horizontal(xsize, 0.0, 0.0); // vetor horizontal de tamanho 4 pois o a tela vai de -2 a 2 horizontalmente 
    glm::vec3 vertical(0.0, ysize, 0.0); // vetor vertical de tamanho 2 pois a tela vai de -1 a -1 verticalmente

    // localização
    glm::vec3 origin(0.0, 0.0, 0.0);

    hitable *list[3];
    list[0] = new sphere(glm::vec3(0, 0, -1), 0.5f, red);
    list[1] = new sphere(glm::vec3(0, -100.5, -1), 100, blue);
    list[2] = new plane(glm::vec3(0, 0.4, -1.6), glm::vec3(0, 1, 0.2), green);

    // int tamanhoList = hitableArraySize(list);
    // std::cout<<tamanhoList;
    hitable *world = new hitable_list(list, std::size(list));

    // printando os pixels
    for(int j = ny-1; j >= 0 ; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j)/ float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);

            glm::vec3 p = r.point_at_parameter(2.0f);

            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }


    return 0;
}
