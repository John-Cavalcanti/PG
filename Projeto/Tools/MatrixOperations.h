#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H
/* 
Essas linhas garantem que o código dentro deste arquivo seja lido apenas uma vez, evitando problemas de duplicação.
*/


#include "Matrix4X4.h"
// includes bibliotecas
#include "../../External/glm/glm.hpp" // forma de importar o glm.hpp
//#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12


inline glm::vec3 pointMatrixMultiplication(float x, float y, float z, Matrix4X4 matrix){
    //funcao que realiza a multiplicacao de uma matriz 4x4 por um ponto 3D
    glm::vec3 result;
    /*
        Estas linhas realizam a multiplicação da matriz pelo ponto. Cada coordenada do ponto resultante é calculada como a soma dos produtos dos elementos correspondentes da matriz e das coordenadas do ponto.
    */
    result.x = matrix.matrix[0][0]*x + matrix.matrix[0][1]*y + matrix.matrix[0][2]*z + matrix.matrix[0][3];
    result.y = matrix.matrix[1][0]*x + matrix.matrix[1][1]*y + matrix.matrix[1][2]*z + matrix.matrix[1][3];
    result.z = matrix.matrix[2][0]*x + matrix.matrix[2][1]*y + matrix.matrix[2][2]*z + matrix.matrix[2][3];

    return result;
}

inline glm::vec3 vectorMatrixMultiplication(float x, float y, float z, Matrix4X4 matrix){
    //funcao que realiza a multiplicacao de uma matriz 4x4 por um vetor 3D
    glm::vec3 result;
    //Esta linha define uma função muito semelhante à pointMatrixMultiplication, mas para vetores em vez de pontos.
    result.x = matrix.matrix[0][0]*x + matrix.matrix[0][1]*y + matrix.matrix[0][2]*z + matrix.matrix[0][3];
    result.y = matrix.matrix[1][0]*x + matrix.matrix[1][1]*y + matrix.matrix[1][2]*z + matrix.matrix[1][3];
    result.z = matrix.matrix[2][0]*x + matrix.matrix[2][1]*y + matrix.matrix[2][2]*z + matrix.matrix[2][3];

    return result;
}


#endif