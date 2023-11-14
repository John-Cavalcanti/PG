#include "../../External/glm/glm.hpp"

class ray
{
public:
    glm::vec3 A; // localização da câmera, ou de onde sairá o raio 
    glm::vec3 B; // direção para onde a câmera está apontada, ou direção que o raio seguirá
    ray();
    ray(const glm::vec3 &a, const glm::vec3 &b);
    glm::vec3 location() const;
    glm::vec3 direction() const;
    glm::vec3 point_at_parameter(float t) const;
};