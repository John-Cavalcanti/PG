// includes c++
#include <iostream>
#include <cmath>
#include <vector>

// includes bibliotecas
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12

// includes .h e C
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

using std::vector;

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

// main
int main() {

    // largura e altura da tela respectivamente // resolução
    int nx = 500; // hres
    int ny = 500;  // vres

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // localização
    glm::vec3 origin(0.0f, 0.0f, 5.0f);

    // para onde a camera esta olhando
    glm::vec3 lookingat(0.0f, 0.0f, -1.0f);

    // vup
    glm::vec3 vup(0.0f, 1.0f, 0.0f);

    // distancia da camera pra tela pra tela
    float distance = 1.0f;

    // lista de objetos

    std::vector<hitable*> lista;

    lista.push_back(new sphere(glm::vec3(2.0, 0.0, -5.0), 0.5f, red));
    lista.push_back(new plane(glm::vec3(0.0, 0.0, -40.0), glm::vec3(0.0, -20.0, 1.0), green));
    lista.push_back(new sphere(glm::vec3(0, -2.0, -5.0), 1, blue));
    // TODO trocar para estrutura de dados vector ou list para alterar dinamicamente

    // numeros de triangulos
    int t = 20;

    // numero total de vertices
    int v = 12;
    
    // Uma lista de vértices (pontos da mesh) 
    vec3 pontos[v] = {
        vec3(-2.0,-0.9742688878808665,-1.1493491916479601),
        vec3(-2.0,-2.0257311121191335,-1.1493491916479601),
        vec3(-1.1493491916479597,-1.5,-1.4742688878808665),
        vec3(-1.474268887880866,-0.6493491916479601,-2.0),
        vec3(-2.525731112119134,-0.6493491916479601,-2.0),
        vec3(-2.8506508083520403,-1.5,-1.4742688878808665),
        vec3(-2.0,-0.9742688878808665,-2.85065080835204),
        vec3(-2.0,-2.0257311121191335,-2.85065080835204),
        vec3(-2.8506508083520403,-1.5,-2.5257311121191335),
        vec3(-1.1493491916479597,-1.5,-2.5257311121191335),
        vec3(-1.474268887880866,-2.35065080835204,-2.0),
        vec3(-2.525731112119134,-2.35065080835204,-2.0)
    };

    // Uma lista com triplas de índices de vértices (cada tripla possui os índices dos vértices (na lista de vértices) que fazem parte de um triângulo)
    triple vertices_index[t] = {
        triple(0,1,2),
        triple(0,3,4),
        triple(0,4,5),
        triple(0,2,3),
        triple(0,5,1),
        triple(6,7,8),
        triple(6,3,9),
        triple(6,4,3),
        triple(6,9,7),
        triple(6,8,4),
        triple(1,10,2),
        triple(1,11,10),
        triple(1,5,11),
        triple(7,10,11),
        triple(7,11,8),
        triple(7,9,10),
        triple(3,2,9),
        triple(10,9,2),
        triple(4,8,5),
        triple(11,5,8),
    }; 

    int v_2 = 4;
    int t_2 = 2;

    vec3 pontos_2[v] = {
        vec3(-1, 0, -6),
        vec3(-1, -1, -4),
        vec3(1,0,-4),
        vec3(1,-1,-6)
    };

    triple vertices_index_2[t]={
        triple(0,1,2),
        triple(0,2,3)
        
    };

    lista.push_back(new tmesh(v, t, pontos, vertices_index, green+red));
    lista.push_back(new tmesh(v_2, t_2, pontos_2, vertices_index_2, green+red));

    
    hitable *world = new hitable_list(lista, lista.size());
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
