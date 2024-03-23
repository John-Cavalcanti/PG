#ifndef TMESH_H
#define TMESH_H
#include "Image.h"
#include "./hitable.h"
#include "./triangle.h"
#include <bits/stdc++.h>
#include "tringle_texture.h"
using std::vector;
using triple = std::tuple<int, int, int>;
using namespace glm;

class tmesh: public hitable {
    public:
        tmesh(int n_vertices, int n_triangulos, vec3 vertices[], triple vertices_index[], color cor, material* om);
        tmesh(vector<vector<glm::vec3>> curves, glm::vec3 color, material* om);
        tmesh(vec3 ref_point, float thickness, color cor, material* om);
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        int n_vertices;
        int n_triangulos;
        std::vector<triangle> triangulos;
        std::vector<textured_triangle> textured_triangles;
        color cor;
        material* objMaterial;
        void translate(float x, float y, float z);
        void rotate(double angle,char axis);
};


#endif
