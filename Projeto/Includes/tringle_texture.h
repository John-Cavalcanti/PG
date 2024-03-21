#ifndef TEXTURED_TRIANGLE_H
#define TEXTURED_TRIANGLE_H

#include "./hitable.h"
#include "Image.h"

class textured_triangle : public hitable {
public:
    textured_triangle() {}
    textured_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 color, material* om, glm::vec2 ta, glm::vec2 tb, glm::vec2 tc);
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;
    glm::vec3 normal;
    material* objMaterial;
    color cor;
    glm::vec2 ta, tb, tc;
    // Inverso da altura do ponto B
    glm::vec3 hb;
    // Inverso da altura do ponto C
    glm::vec3 hc; 
    Image* texture;  // Adicione um ponteiro para a imagem de textura
};

#endif // TEXTURED_TRIANGLE_H