#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"
#include "color.h"
#include "./material.h"
#include "../../External/glm/glm.hpp"

// Classe do Livro : ShadeRec e GeometricObject pag 53 do livro
struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    color cor;
    float kdif; // kd
    float kamb; // ka
    float kespc; // ks
    float kref;
    float ktrans;
    float rug;
    float refra;
};

class hitable { 
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
        material* objMaterial;
};

#endif