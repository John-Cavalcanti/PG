#include "./tmesh.h"

#include <iostream>
#include "../Tools/MatrixOperations.h"
#include "../Tools/Matrix4X4.h"
using std::vector;
float combination(float n, float k);
// construtor do tmesh

tmesh::tmesh(int n_vertices, int n_triangulos, vec3 vertices[], triple vertices_index[], color cor, material* om): n_vertices(n_vertices), n_triangulos(n_triangulos),cor(cor), objMaterial(om) {
    // cria os triangulos com base nos parametros passados e insere no vector de triangulos
    for (int i = 0; i< n_triangulos; i++){
        vec3 A = vertices[std::get<0>(vertices_index[i])];
        vec3 B = vertices[std::get<1>(vertices_index[i])];
        vec3 C = vertices[std::get<2>(vertices_index[i])];
        triangulos.push_back(triangle(A, B, C, cor, objMaterial));
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

tmesh::tmesh(vector<vector<glm::vec3>> curves, glm::vec3 color, material* om): cor(color), objMaterial(om) {
    vector<glm::vec3> surfacePoints;

    int nCurves = curves.size();
    int nPoints = curves[0].size();

    for (float t0 = 0; t0 <= 1.f; t0 += 0.1) { // Ajuste o valor 0.01 para controlar a resolução da malha
        for (float t1 = 0; t1 <= 1.f; t1 += 0.1) {
            glm::vec3 resultPoint(0.0f);

            for (int i = 0; i < nCurves; i++) {
                float f1 = combination(nCurves - 1, i) * std::pow(t0, i) * std::pow(1 - t0, nCurves - 1 - i);
                
                glm::vec3 innerPoint(0.0f);

                for (int j = 0; j < nPoints; j++) {
                    glm::vec3 point = curves[i][j];

                    float f2 = combination(nPoints - 1, j) * std::pow(t1, j) * std::pow(1 - t1, nPoints - 1 - j);
                    
                    point *= f2;

                    innerPoint += point;
                }

                resultPoint += innerPoint * f1;
            }

            surfacePoints.push_back(resultPoint);
        }
    }

    for (int i = 0; i < surfacePoints.size() - 2; i++) {
        glm::vec3 A = surfacePoints[i];
        glm::vec3 B = surfacePoints[i+1];
        glm::vec3 C = surfacePoints[i+2];
        triangulos.push_back(triangle(A, B, C, color, om));
    }
}

// Função para calcular coeficientes binomiais
float combination(float n, float k) {
    if (k == 0 || k == n) {
        return 1;
    } else if (k > n) {
        return 0;
    } else {
        float result = 1;
        for (int i = 1; i <= k; ++i) {
            result *= n - k + i;
            result /= i;
        }
        return result;
    }
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

        tri = triangle(tri.a, tri.b, tri.c, tri.cor, objMaterial);

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

