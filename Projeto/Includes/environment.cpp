#include "environment.h"

// Define o construtor da classe Environment
// O construtor recebe a luz ambiente
// O valor é usado para inicializar o atributo da classe
Environment::Environment(const glm::vec3& ambientLight)
    : ambientLight(ambientLight) {}

// Define o metodo getAmbientLight da classe Environment
// O metodo retorna a luz ambiente como um vetor de 3 dimensoes com valores inteiros
// Os valores representam a intensidade da luz ambiente em cada canal de cor (RGB)
glm::vec3 Environment::getAmbientLight() const {
    return ambientLight;
}