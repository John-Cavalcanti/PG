#ifndef MATERIAL_H
#define MATERIAL_H

#include "../../External/glm/glm.hpp"
using glm::vec3;

class material
{
    public:
        // implementacao de coeficientes
        /* kd = difuso
        *  ka = ambiental (quanto esse objeto reage a luz ambiental)
        *  ks = especular
        *  kr = reflexao 
        *  kt = transmissao
        *  n = rugosidade       
        */
        float kd, ka, ks, kr, kt, n, refrId;
        material();
        material(float ckd, float cka, float cks, float ckr, float ckt, float cn, float crefrId); // c = constructor
};

#endif