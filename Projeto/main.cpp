#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12
#include "./Includes/ray.h"
#include "./Includes/color.h"

// cores basicas para testes com objetos
const color red = glm::vec3(255.99,0.0,0.0);
const color green = glm::vec3(0.0,255.99,0.0);
const color blue = glm::vec3(0.0,0.0,255.99);

float hit_sphere(const glm::vec3& center, float radius, const ray& r) // função que checa se o ray se intercepta com a esfera
{
    glm::vec3 oc = r.location() - center; // vetor que vai do centro da esfera até a origem do raio
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius; // calcula o dot product de oc com ele mesmo, e subtrai o raio ao quadrado
    //a, b e c são os coeficientes da equação de segundo grau
    float discriminant = b*b - 4*a*c;
    if(discriminant < 0)
    {
        return -1.0f;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0f*a);
    }
}


// função que define a cor que será exibida
color ray_color(const ray& r)
{
    // declarando uma esfera e sua cor
    float t = hit_sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);// checa se o raio intercepta a esfera
    if(t > 0.0){
        
        /*glm::vec3 N = normalize(r.point_at_parameter(t) - glm::vec3(0.0f, 0.0f, -1.0f));// calcula o vetor normal
        return 0.5f * color(N.x + 1.0f, N.y + 1.0f, N.z + 1.0f); // retorna a cor*/
        
        return red; // mudar esse retorno para a cor do objeto que está sendo hittado
    }

    color backgroundColor = glm::vec3(0.0,0.0,0.0); // cor preta pro background
    
    /*
    color startColor(1.0f, 1.0f, 1.0f);
    color endColor(0.5f, 0.7f, 1.0f);
    glm::vec3 unit_direction = normalize(r.direction());
    t = 0.5f * (unit_direction.y + 1.0f);
    return ((1.0f - t) * startColor) + (t * endColor);*/

    return backgroundColor;
}

struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
};

class hitable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

class sphere: public hitable {
    public:
        sphere() {}
        sphere(glm::vec3 cen, float r) : center(cen), radius(r) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        glm::vec3 center;
        float radius;
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
            return true;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
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

int main() {

    // largura e altura da tela respectivamente // resolução
    int nx = 1000; // lres
    int ny = 500;  // hres

    // proporção da tela em uma fração
    float proportionYX = float(ny) / float(nx);

    // tamanho da tela proporcional
    float xsize = 1.0f;
    float ysize = xsize * proportionYX;


    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // definindo localização da camera, e os vetores ortonormais
    // no momento tem apenas dois vetores ortonormais o horizontal e o vertical
    // o vetor horizontal deve ter o dobro do vertical visto que a largura da tela é o dobro da altura
    glm::vec3 lower_left_corner(-xsize/2, -ysize/2, -ysize/2); // posição do canto inferior esquerdo da tela
    glm::vec3 horizontal(xsize, 0.0, 0.0); // vetor horizontal de tamanho 4 pois o a tela vai de -2 a 2 horizontalmente 
    glm::vec3 vertical(0.0, ysize, 0.0); // vetor vertical de tamanho 2 pois a tela vai de -1 a -1 verticalmente

    // localização
    glm::vec3 origin(0.0, 0.0, 0.0);

    hitable *list[2];
    list[0] = new sphere(glm::vec3(0, 0, -1), 0.5f);
    list[1] = new sphere(glm::vec3(0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    // printando os pixels
    for(int j = ny-1; j >= 0 ; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j)/ float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);

            glm::vec3 p = r.point_at_parameter(2.0f);
 
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }


    return 0;
}
