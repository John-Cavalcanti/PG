#include <iostream>
#include "../External/glm/glm.hpp" // forma de importar o glm.hpp
#include "../External/glm/gtx/vector_angle.hpp"
#include <list>
#include <vector>

using namespace glm;
using namespace std;

int main() {

    vec3 a1 = normalize(vec3(1.0f,0.0f,0.0f));
    vec3 a2 = normalize(vec3(-1.0f,-1.0f,-1.0f));

    float angRad = glm::angle(a1,a2);

    cout << "radianos: "<< angRad; 

    float ang = degrees(angRad);

    cout <<"\noutput: " << ang;

    return 0;
}
