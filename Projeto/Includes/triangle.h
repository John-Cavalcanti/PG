#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "./hitable.h"

class triangle: public hitable {
    public:
        triangle() {}
        triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2,  glm::vec3 n, glm::vec3 c):v0(v0), v1(v1), v2(v2), normal(n), cor(c) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        glm::vec3 v0;
        glm::vec3 v1;
        glm::vec3 v2;
        glm::vec3 normal;
        color cor;
};


#endif
