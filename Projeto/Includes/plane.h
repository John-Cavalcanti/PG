#ifndef PLANE_H
#define PLANE_H

#include "./hitable.h"

// plano 
class plane: public hitable {
    public:
        plane() {}
        plane(glm::vec3 p, glm::vec3 n, color c, material* om) : plane_point(p), normal(normalize(n)), cor(c), objMaterial(om) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        glm::vec3 plane_point;
        glm::vec3 normal;
        color cor;
        material* objMaterial;
        void translade(float x, float y, float z);
        void rotate(double angle, char axis);
};


#endif