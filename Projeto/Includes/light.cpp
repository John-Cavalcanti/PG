#include "light.h"
// Define o construtor da classe Light
// O construtor recebe a posicao da luz e a intensidade
// Os valores sao usados para inicializar os atributos da classe
Light::Light(const glm::vec3& position, const glm::ivec3& intensity)
    : position(position), intensity(intensity) {}

// Define o metodo getPosition da classe Light
// O metodo retorna a posicao da luz como um vetor de 3 dimensoes
glm::vec3 Light::getPosition() const {
    return position;
}

// Define o metodo getIntensity da classe Light 
// O metodo retorna a intensidade da luz como um vetor de 3 dimensoes com valores inteiros
// Os valores representam a intensidade da luz em cada canal de cor (RGB)
glm::ivec3 Light::getIntensity() const {
    return intensity;
}