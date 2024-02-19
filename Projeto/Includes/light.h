#ifndef LIGHT_H
#define LIGHT_H

#include "../../External/glm/glm.hpp"

class Light {
public:
    // Construtor da classe Light
    // O construtor recebe a posicao da luz, a intensidade e a luz ambiente
    Light(const glm::vec3& position, const glm::ivec3& intensity, const glm::ivec3& ambientLight);
    // Metodo getPosition da classe Light
    glm::vec3 getPosition() const;
    // Metodo getIntensity da classe Light
    // A instensidade da luz é represntada como uma cor RGB, cada componente no intervalo [0, 255]
    glm::ivec3 getIntensity() const;
    // Metodo getAmbientLight da classe Light
    // A luz ambiente é represntada como uma cor RGB, cada componente no intervalo [0, 255]
    glm::ivec3 getAmbientLight() const;

private:
    glm::vec3 position;
    glm::ivec3 intensity;
    glm::ivec3 ambientLight;
};

#endif // LIGHT_H