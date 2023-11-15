#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "headers/calculator.h"

int main() {

    calculator calculadora;

    int soma = calculadora.sum(1,2);

    std::cout << soma << "\n";

    return 0;
}
