#include "./tmesh.h"
#include <iostream>
#include "../Tools/MatrixOperations.h"
#include "../Tools/Matrix4X4.h"
#include "tringle_texture.h"
using std::vector;
float combination(float n, float k);

vec3 get_torus_point(float theta, float alpha, vec3 center, float radius);

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
    // chama o metodo hit de cada triangulo texturizado dentro da mesh
    for (textured_triangle t: textured_triangles){
        if(t.hit(r, t_min, closest_so_far, rec)){
            mesh_hit = true;
            closest_so_far = rec.t;
        }
    }
    return mesh_hit;
}
// Resumo: Este é o construtor para a classe tmesh. Ele recebe um vetor de curvas (cada curva é um vetor de pontos 3D),
// uma cor e um material. O construtor calcula os pontos da superfície de Bézier usando as curvas de entrada e cria
// triângulos a partir desses pontos. Os triângulos são armazenados no vetor 'triangulos'.

// Início do construtor tmesh
tmesh::tmesh(vector<vector<glm::vec3>> curves, glm::vec3 color, material* om): cor(color), objMaterial(om) {
    vector<vector<glm::vec3>> surfacePoints;
    vector<vector<glm::vec2>> textureCoords;

    int nCurves = curves.size();
    int nPoints = curves[0].size();

    // t1 e t0 são usados para informar a quantidade de pontos, que implica na resolução da malha
    for (float t0 = 0; t0 <= 1.f; t0 += 0.1) { // Ajuste o valor 0.01 para controlar a resolução da malha
        vector<glm::vec3> row;
        vector<glm::vec2> texRow;
        for (float t1 = 0; t1 <= 1.f; t1 += 0.1) {
            glm::vec3 resultPoint(0.0f);

            for (int i = 0; i < nCurves; i++) {
                // fórmula de bezier calculando pontos baseado na primeira curva
                float f1 = combination(nCurves - 1, i) * std::pow(t0, i) * std::pow(1 - t0, nCurves - 1 - i);
                
                glm::vec3 innerPoint(0.0f);

                for (int j = 0; j < nPoints; j++) {
                    glm::vec3 point = curves[i][j];

                    // fórmula de bezier calculando pontos baseado na segunda curva
                    float f2 = combination(nPoints - 1, j) * std::pow(t1, j) * std::pow(1 - t1, nPoints - 1 - j);
                    
                    point *= f2;

                    innerPoint += point;
                }

                resultPoint += innerPoint * f1;
            }

            row.push_back(resultPoint);
            texRow.push_back(glm::vec2(t0, t1));
        }
        surfacePoints.push_back(row);
        textureCoords.push_back(texRow);
    }

    // pontos da superfícies gerados sendo percorridos para gerar quadriláteros
    // os pontos dos triângulos são os pontos da superfície
    Image* texture = new Image("Includes/imagens_Test/toro_50divisions.png");
    for (int i = 0; i < surfacePoints.size() - 1; i++) {
        for (int j = 0; j < surfacePoints[i].size() - 1; j++) {
            glm::vec3 A = surfacePoints[i][j];
            glm::vec3 B = surfacePoints[i+1][j];
            glm::vec3 C = surfacePoints[i][j+1];
            glm::vec3 D = surfacePoints[i+1][j+1];
            glm::vec2 Atex = textureCoords[i][j];
            glm::vec2 Btex = textureCoords[i+1][j];
            glm::vec2 Ctex = textureCoords[i][j+1];
            glm::vec2 Dtex = textureCoords[i+1][j+1];
            textured_triangles.push_back(textured_triangle(B, A, C, color, om,Btex, Atex, Ctex, texture));
            textured_triangles.push_back(textured_triangle(B, C, D, color, om, Btex, Ctex, Dtex, texture));
        }
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

// construtor do toro
tmesh::tmesh(vec3 center, float radius, color cor, material* om){
    int divisions = 10; // quanto maior esse valor, mais triangulos serão usados

    const float pi = 3.14159265358979323846;
    vector<vec3> row1;
    vector<vec3> row2;

    for (int theta_index = 0; theta_index < divisions+1; theta_index++){

        row1.assign(row2.begin(), row2.end()); // copia o conteúdo de row2 para row1
        row2.clear(); // apaga todos os pontos de row2

        for (int alpha_index = 0; alpha_index < divisions; alpha_index++){
            float cur_alpha = alpha_index * 2 * pi / divisions-1; // angulo alfa atual em radianos
            float cur_theta = theta_index * 2 * pi / divisions; // angulo teta atual em radianos

            // pega um ponto do torus com base nos angulos teta e alfa
            vec3 triangle_point = get_torus_point(cur_theta, cur_alpha, center, radius);

            row2.push_back(triangle_point);
        }

        if (theta_index > 0 ){

            for (int i = 0; i < divisions; i++){

                int next_pos = (i+1)%(divisions);

                vec3 point1 = row1[i];
                vec3 point2 = row1[next_pos];
                vec3 point3 = row2[i];
                vec3 point4 = row2[next_pos];

                // Usa dois triangulos para formar um quadrado
                triangle triangle1 = triangle(point1, point3, point4, cor, om);
                triangle triangle2 = triangle(point1, point4, point2, cor, om);
                
                triangulos.push_back(triangle1);
                triangulos.push_back(triangle2);
            }
        }
    }
}

// função que calcula os pontos do toro
vec3 get_torus_point(float theta, float alpha, vec3 center, float radius){
    float x = (center.y + radius * cos(theta)) * sin(alpha);
    float y = (center.y + radius * cos(theta)) * cos(alpha);
    float z = center.z + radius * sin(theta);

    return vec3(x,y,z);
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

