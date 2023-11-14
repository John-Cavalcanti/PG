#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "calculator.h"

int main() {
    int x,y;

    calculator calculadora;

    int soma = calculadora.sum(5,4);

    std::cout << soma;
    return 0;
}