#ifndef COLOR_H
#define COLOR_H

#include "../../External/glm/glm.hpp"

#include <iostream>

using color = glm::vec3;

void write_color(std::ostream &out, color pixel_color) {

    int ir = int(255.99*pixel_color[0]);
    int ig = int(255.99*pixel_color[1]);
    int ib = int(255.99*pixel_color[2]);

    out << ir << " " << ig << " " << ib << "\n";
    
}

#endif