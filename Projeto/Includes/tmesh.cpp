#include "./tmesh.h"

// construtor do tmesh
tmesh::tmesh(int n_vertices, int n_triangulos, vec3 vertices[], vec3 vertices_index[], color cor): n_vertices(n_vertices), n_triangulos(n_triangulos),cor(cor) {
    for (int i = 0; i< n_triangulos; i++){
        vec3 A = vertices[int(vertices_index[i].x)];
        vec3 B = vertices[int(vertices_index[i].y)];
        vec3 C = vertices[int(vertices_index[i].z)];
        triangulos.push_back(triangle(A, B, C, cor));
    }
};

bool tmesh::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{   
    bool mesh_hit = false;
    for (triangle t: triangulos){
        if(t.hit(r, t_min, t_max, rec)){
            mesh_hit = true;
        }
    }
    return mesh_hit;
}