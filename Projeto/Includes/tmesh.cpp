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

/*
Este método rotaciona cada triângulo na malha em torno de um eixo específico por um ângulo específico. 
Ele cria uma matriz de rotação usando o ângulo e o eixo fornecidos e, em seguida, multiplica cada ponto de cada triângulo por essa matriz de rotação. 
O resultado é uma nova malha onde cada triângulo foi rotacionado pelo ângulo angle em torno do eixo axis.
*/

void tmesh::rotate(double angle, char axis) {
    Matrix4X4 rotationMatrix;
    rotationMatrix.toRotationMatrix(angle, axis);

    for (auto& tri : triangulos) {
        tri.a = pointMatrixMultiplication(tri.a.x, tri.a.y, tri.a.z, rotationMatrix);
        tri.b = pointMatrixMultiplication(tri.b.x, tri.b.y, tri.b.z, rotationMatrix);
        tri.c = pointMatrixMultiplication(tri.c.x, tri.c.y, tri.c.z, rotationMatrix);

        tri = triangle(tri.a, tri.b, tri.c, tri.cor);

    }
}

/*
Este método translada (move) cada triângulo na malha ao longo dos eixos x, y e z. 
Ele cria uma matriz de translação usando os valores x, y e z fornecidos e, em seguida, multiplica cada ponto de cada triângulo por essa matriz de translação. 
O resultado é uma nova malha onde cada triângulo foi transladado pelas quantidades x, y e z.
*/
void tmesh::translate(float x, float y, float z){
    Matrix4X4 translationMatrix;
    translationMatrix.toTranslationMatrix(x, y, z);

    for (auto& tri : triangulos) {
        tri.a = pointMatrixMultiplication(tri.a.x, tri.a.y, tri.a.z, translationMatrix);
        tri.b = pointMatrixMultiplication(tri.b.x, tri.b.y, tri.b.z, translationMatrix);
        tri.c = pointMatrixMultiplication(tri.c.x, tri.c.y, tri.c.z, translationMatrix);
    }
}

