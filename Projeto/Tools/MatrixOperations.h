#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H

#include "Matrix4X4.h"
// includes bibliotecas
#include "../../External/glm/glm.hpp" // forma de importar o glm.hpp
//#include "../External/glm/gtc/matrix_transform.hpp" // essa diretiva é necessária pra executar o código da linha 12


inline glm::vec3 pointMatrixMultiplication(float x, float y, float z, Matrix4X4 matrix){
    //funcao que realiza a multiplicacao de uma matriz 4x4 por um ponto 3D
    glm::vec3 result;

    result.x = matrix.matrix[0][0]*x + matrix.matrix[0][1]*y + matrix.matrix[0][2]*z + matrix.matrix[0][3];
    result.y = matrix.matrix[1][0]*x + matrix.matrix[1][1]*y + matrix.matrix[1][2]*z + matrix.matrix[1][3];
    result.z = matrix.matrix[2][0]*x + matrix.matrix[2][1]*y + matrix.matrix[2][2]*z + matrix.matrix[2][3];

    return result;
}

inline glm::vec3 vectorMatrixMultiplication(float x, float y, float z, Matrix4X4 matrix){
    //funcao que realiza a multiplicacao de uma matriz 4x4 por um vetor 3D
    glm::vec3 result;

    result.x = matrix.matrix[0][0]*x + matrix.matrix[0][1]*y + matrix.matrix[0][2]*z + matrix.matrix[0][3];
    result.y = matrix.matrix[1][0]*x + matrix.matrix[1][1]*y + matrix.matrix[1][2]*z + matrix.matrix[1][3];
    result.z = matrix.matrix[2][0]*x + matrix.matrix[2][1]*y + matrix.matrix[2][2]*z + matrix.matrix[2][3];

    return result;
}


#endif