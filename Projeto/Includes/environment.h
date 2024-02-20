#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "../../External/glm/glm.hpp"

class Environment {
public:
    // Construtor da classe Environment
    // O construtor recebe a luz ambiente
    Environment(const glm::ivec3& ambientLight);
    // Metodo getAmbientLight da classe Environment
    // A luz ambiente é represntada como uma cor RGB, cada componente no intervalo [0, 255]
    glm::ivec3 getAmbientLight() const;

private:
    glm::ivec3 ambientLight;
};

#endif // ENVIRONMENT_H