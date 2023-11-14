#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "./Includes/ray.h"
/*
glm::vec3 color(const ray& r)
{
    glm::vec3 aux1(1.0,1.0,1.0);
    glm::vec3 unit_direction = normalize(r.direction());
    double t = 0.5 * (unit_direction.y + 1.0);
    return aux1;
}*/

int main() {

    glm::vec3 vetor1(1.0,1.0,1.0);

    std::cout << vetor1.y << "\n";

    return 0;
}