#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12
#include "./Includes/ray.h"

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
glm::vec3 color(const ray& r)
{
    float t = hit_sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, r);// checa se o raio intercepta a esfera
    if(t > 0.0){
        glm::vec3 N = normalize(r.point_at_parameter(t) - glm::vec3(0.0f, 0.0f, -1.0f));// calcula o vetor normal
        return 0.5f * glm::vec3(N.x + 1.0f, N.y + 1.0f, N.z + 1.0f); // retorna a cor
    }
    glm::vec3 aux1(1.0f, 1.0f, 1.0f);
    glm::vec3 aux2(0.5f, 0.7f, 1.0f);
    glm::vec3 unit_direction = normalize(r.direction());
    t = 0.5f * (unit_direction.y + 1.0f);
    return ((1.0f - t) * aux1) + (t * aux2);
}

int main() {

    // largura e altura da tela respectivamente
    int nx = 1060;
    int ny = 900;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // definindo localização da camera, e os vetores ortonormais
    glm::vec3 lower_left_corner(-2.0, -1.0, -1.0);
    glm::vec3 horizontal(4.0, 0.0, 0.0);
    glm::vec3 vertical(0.0, 2.0, 0.0);

    // localização
    glm::vec3 origin(0.0, 0.0, 0.0);

    // printando os pixels
    for(int j = ny-1; j >= 0 ; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            float u = float(i) / float(nx);
            float v = float(j)/ float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);

            glm::vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n"; 
        }
    }


    return 0;
}
