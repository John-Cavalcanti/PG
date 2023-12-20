#include "./tmesh.h"

#include <iostream>
#include "../Tools/MatrixOperations.h"
#include "../Tools/Matrix4X4.h"
// construtor do tmesh
tmesh::tmesh(int n_vertices, int n_triangulos, vec3 vertices[], triple vertices_index[], color cor): n_vertices(n_vertices), n_triangulos(n_triangulos),cor(cor) {
    // cria os triangulos com base nos parametros passados e insere no vector de triangulos
    for (int i = 0; i< n_triangulos; i++){
        vec3 A = vertices[std::get<0>(vertices_index[i])];
        vec3 B = vertices[std::get<1>(vertices_index[i])];
        vec3 C = vertices[std::get<2>(vertices_index[i])];
        triangulos.push_back(triangle(A, B, C, cor));
    }
};

bool tmesh::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{   
    bool mesh_hit = false;
    double closest_so_far = t_max;
    // chama o metodo hit de cada triangulo dentro da mesh
    for (triangle t: triangulos){
        if(t.hit(r, t_min, closest_so_far, rec)){
            mesh_hit = true;
            closest_so_far = rec.t;
        }
    }
    return mesh_hit;
}

void tmesh::translate(float x, float y, float z){
    Matrix4X4 translationMatrix;
    translationMatrix.toTranslationMatrix(x, y, z);

    for (auto& tri : triangulos) {
        tri.a = pointMatrixMultiplication(tri.a.x, tri.a.y, tri.a.z, translationMatrix);
        tri.b = pointMatrixMultiplication(tri.b.x, tri.b.y, tri.b.z, translationMatrix);
        tri.c = pointMatrixMultiplication(tri.c.x, tri.c.y, tri.c.z, translationMatrix);
    }
}

void tmesh::rotate(double angle, char axis){
    // Calcular o centro da malha
    vec3 center = calculateCenter();

    // Transladar a malha para a origem
    
    translate(-center.x, -center.y, -center.z);

    // Criar a matriz de rotação
    Matrix4X4 rotationMatrix;
    rotationMatrix.toRotationMatrix(angle, axis);
    // Aplicar a rotação
    for (auto& tri : triangulos) {
        tri.a = pointMatrixMultiplication(tri.a.x, tri.a.y, tri.a.z, rotationMatrix);
        tri.b = pointMatrixMultiplication(tri.b.x, tri.b.y, tri.b.z, rotationMatrix);
        tri.c = pointMatrixMultiplication(tri.c.x, tri.c.y, tri.c.z, rotationMatrix);
    }

    // Transladar a malha de volta para sua posição original
    translate(center.x, center.y, center.z);
}

vec3 tmesh::calculateCenter() {
    vec3 sum(0.0f, 0.0f, 0.0f);
    int count = 0;

    for (const auto& tri : triangulos) {
        sum += tri.a;
        sum += tri.b;
        sum += tri.c;
        count += 3;
    }

    return sum / static_cast<float>(count);
}