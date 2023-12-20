#include "./camera.h"

camera::camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vres, float  hres, float dist, float vfov)
{
    w = glm::normalize(lookfrom - lookat);
    u = glm::normalize(glm::cross(vup,w));
    v = glm::cross(w,u);
    
    origem = lookfrom;
    float aspect_ratio = hres / vres;
    
    // tamanho da largura e altura
    float theta = glm::radians(vfov);
    float half_height = tan(theta/2);
    float half_width = aspect_ratio * half_height;
    
    //lower_left_corner = glm::vec3(-half_width, -half_height, -1.0);
    lower_left_corner = origem - half_width*u -half_height*v - w;
    
    horizontal = 2*half_width*u;
    vertical = 2*half_height*v;
}

ray camera::get_ray(float s, float t)
{
    return ray(origem, lower_left_corner + s*horizontal + t*vertical - origem);
}
