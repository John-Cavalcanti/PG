#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "./hitable.h"

class triangle: public hitable {
    public:
        triangle() {}
        triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c,  glm::vec3 n, glm::vec3 color):a(a), b(b), c(c), normal(n), cor(color) {
            // vetor da aresta entre a e b
            glm::vec3 u = b - a;

            //vetor da aresta entre a e c
            glm::vec3 v = c - a;

            //projecao do vetor u em v
            glm::vec3 projuv = dot(u,v)/dot(v,v) * v;

            //projecao do vetor v em u
            glm::vec3 projvu = dot(v,u)/dot(u,u) * u;

            // altura do ponto B
            hb = u - projuv;

            // normalização inversa da altura hb
            hb = hb/dot(hb,hb);

            // altura do ponto C
            hc = v - projvu;

            // normalização inversa da altura hc
            hc = hc/dot(hc,hc);

        };
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        glm::vec3 a;
        glm::vec3 b;
        glm::vec3 c;
        glm::vec3 normal;
        color cor;

        glm::vec3 hb;
        glm::vec3 hc;

};


#endif
