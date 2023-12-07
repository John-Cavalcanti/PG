#ifndef TMESH_H
#define TMESH_H

#include "./hitable.h"
#include "./triangle.h"
#include <bits/stdc++.h>

using namespace glm;

class tmesh: public hitable {
    public:
        tmesh(int n_vertices, int n_triangulos, vec3 vertices[], vec3 vertices_index[], color cor);
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        int n_vertices;
        int n_triangulos;
        std::vector<triangle> triangulos;
        color cor;
};


#endif
