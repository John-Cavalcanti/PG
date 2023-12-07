#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12
#include "./Includes/ray.h"
#include "./Includes/color.h"
#include "./Includes/hitable.h"
#include "./Includes/spheres.h"
#include "./Includes/plane.h"
#include "./Includes/hitable_list.h"
#include "./Includes/camera.h"
#include "./Includes/triangle.h"
#include "./Includes/tmesh.h"
#include <cmath>
#include "float.h"

#define M_PI 3.14159265358979323846 

// cores basicas para testes com objetos
const color red(1.0f,0.0f,0.0f);
const color green(0.0f,1.0f,0.0f);
const color blue(0.0f,0.0f,1.0f);

// função que define a cor que será exibida
color ray_color(const ray& r, hitable *world)
{
    hit_record rec;
    if(world->hit(r, 0.0f, FLT_MAX, rec)){
        return rec.cor;
    }

    color backgroundColor = glm::vec3(0.0,0.0,0.0); // cor preta pro background

    return backgroundColor;
}

// TODO Implementar classe compound caso a classe hitable_list não seja ideal para implementar a malha


// main
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
    // TODO trocar para estrutura de dados vector ou list para alterar dinamicamente
    hitable *list[4];
    list[0] = new sphere(glm::vec3(2.0, 0.0, -5.0), 0.5f, red);
    list[1] = new plane(glm::vec3(0.0, 0.0, -40.0), glm::vec3(0.0, -20.0, 1.0), green);
    list[2] = new sphere(glm::vec3(0, -2.0, -5.0), 1, blue);

    // numeros de triangulos
    int t = 2;

    // numero total de vertices
    int v = 4;
    // pontos da mesh
    vec3 pontos[v] = {
        vec3(-6,-4,-5),
        vec3(-3,-1,-5),
        vec3(-6,0,-5),
        vec3(-17,-2,-11)
    };

    triple vertices_index[t] = {
        triple(0, 2, 3),
        triple(0, 1, 2)
    }; 
    list[3] = new tmesh(v, t, pontos, vertices_index, green+red);
    // list[3] = new triangle(glm::vec3(-6,-4,-5),glm::vec3(-3,-1,-5),glm::vec3(-6,-0.2f,-5), red+green);
    //list[3] = new sphere(glm::vec3(-1.5, 0, -5), 0.5f, blue + green);
    
    hitable *world = new hitable_list(list, std::size(list));

    camera *cam = new camera(origin, lookingat, vup, ny, nx, distance);

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
