#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp

int main() {
    glm::vec3 v1(1.0f, 2.0f, 3.0f);
    glm::vec3 v2(4.0f, 5.0f, 6.0f);

    glm::vec3 result = v1 + v2;

    std::cout << "Result: (" << result.x << ", " << result.y << ", " << result.z << ")\n";

    return 0;
}
