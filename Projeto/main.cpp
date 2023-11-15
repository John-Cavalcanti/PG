#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtc/matrix_transform.hpp"
#include "./includes/ray.h"

// função que define a cor que será exibida
glm::vec3 color(const ray& r)
{
    glm::vec3 aux1(1.0f, 1.0f, 1.0f);
    glm::vec3 aux2(0.5f, 0.7f, 1.0f);
    glm::vec3 unit_direction = normalize(r.direction());
    float t = 0.5f * (unit_direction.y + 1.0f);
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
