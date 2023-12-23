#include "Matrix4X4.h"
#include <cmath>

Matrix4X4::Matrix4X4() {}

void Matrix4X4::toTranslationMatrix(float x, float y, float z) {// o objetivo é transformar 
// a matriz atual em uma matriz de translaçao. Os valores de x, y e z representao quantidade de translacoes ao longo dos eixos
    matrix[0][3] = x; // coloco o valor de x na primeira linha e ultima coluna da matriz. Este valor representa a quantidade de movimento ao longo do eixo x
    matrix[1][3] = y;
    matrix[2][3] = z;
}

void Matrix4X4::toRotationMatrix(double angle, char axis) { // é um método da classe que modifica a matriz para representar 
    // uma rotação de um eixo específico por um angulo específico
    // o angle é o angulo de rotacao em graus
    double rad = angle * M_PI / 180.0f; // convertendo para radianos, ja que as funcoes trigonometricas em c++ usam radianos
    switch (axis) { // o char axis é o eixo que vai ser rotacionado 
        // para cada caso ("x", "y" ou "z") a matriz é preenchida com valores apropriados para representar 
        // uma rotacao em torno desse eixo 
        case 'x':
        // os valores sao calculados usando as funcoes cos e sin do angulo de rotacao em radianos 
        // os sinais negativos sao usados para representar a direcao da rotacao 
        // Por exemplo, para o caso 'x', a matriz é preenchida da seguinte maneira:
            matrix[1][1] = (float) std::cos(rad); 
            matrix[1][2] = (float) (-std::sin(rad));
            matrix[2][1] = (float) std::sin(rad);
            matrix[2][2] = (float) std::cos(rad);
            break;
        /*
        Isso significa que a rotação ocorre em torno do eixo x. As linhas 2 e 3 da matriz são modificadas para representar a rotação.
        As funções cos e sin são usadas para calcular os novos valores, e o sinal negativo é usado para representar a direção da rotação.
        As linhas 1 e 4 da matriz não são modificadas, pois a rotação ocorre em torno do eixo x.
        */
        case 'y':
            matrix[0][0] = (float) std::cos(rad);
            matrix[0][2] = (float) std::sin(rad);
            matrix[2][0] = (float) (-std::sin(rad));
            matrix[2][2] = (float) std::cos(rad);
            break;
        case 'z':
            matrix[0][0] = (float) std::cos(rad);
            matrix[0][1] = (float) (-std::sin(rad));
            matrix[1][0] = (float) std::sin(rad);
            matrix[1][1] = (float) std::cos(rad);
            break;
    }
}

void Matrix4X4::toClockwiseRotationMatrix(double angle, char axis){// A diferenca desse metodo para o anterior é que ele
// representa uma rotacao no sentido horario, entao os sinais sao invertidos
    double rad = angle * M_PI / 180.0f;
    switch (axis) {
        case 'x':
            matrix[1][1] = (float) std::cos(rad);
            matrix[1][2] = (float) std::sin(rad);
            matrix[2][1] = (float) (-std::sin(rad));
            matrix[2][2] = (float) std::cos(rad);
            break;
        case 'y':
            matrix[0][0] = (float) std::cos(rad);
            matrix[0][2] = (float) (-std::sin(rad));
            matrix[2][0] = (float) std::sin(rad);
            matrix[2][2] = (float) std::cos(rad);
            break;
        case 'z':
            matrix[0][0] = (float) std::cos(rad);
            matrix[0][1] = (float) std::sin(rad);
            matrix[1][0] = (float) (-std::sin(rad));
            matrix[1][1] = (float) std::cos(rad);
            break;
    }
}