#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "./hitable.h"

class triangle: public hitable {
    public:
        triangle() {}
        triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 color, material* om) : a(a), b(b), c(c), cor(color), objMaterial(om){};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        glm::vec3 a;
        glm::vec3 b;
        glm::vec3 c;
        glm::vec3 normal;
        material* objMaterial;
        color cor;

        // Inverso da altura do ponto B
        glm::vec3 hb;
        // Inverso da altura do ponto C
        glm::vec3 hc;

};


#endif
