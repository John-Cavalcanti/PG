#include "./triangle.h"

bool triangle::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    float t = glm::dot((v1 - r.location()), normal) / glm::dot(r.direction(), normal);

    if (t < t_max && t > t_min)
    { // Teve interseção com o plano do triângulo
        // Ponto de interseção:
        glm::vec3 pontoIntersecao = r.point_at_parameter(t);

        const float EPSILON = 0.000001f;
        glm::vec3 edge1 = v1 - v0;
        glm::vec3 edge2 = v2 - v0;
        glm::vec3 h = glm::cross(r.direction(), edge2);
        float a = glm::dot(edge1, h);

        if (a > -EPSILON && a < EPSILON)
            return false; // O raio é paralelo ao triângulo

        float f = 1.0f / a;
        glm::vec3 s = r.location() - v0;
        float u = f * glm::dot(s, h);

        if (u < 0.0f || u > 1.0f)
            return false;

        glm::vec3 q = glm::cross(s, edge1);
        float v = f * glm::dot(r.direction(), q);

        if (v < 0.0f || u + v > 1.0f)
            return false;

        float t = f * glm::dot(edge2, q);

        if (t > t_min && t < t_max)
        {
            rec.t = t;
            rec.p = r.point_at_parameter(t);
            rec.normal = glm::normalize(glm::cross(edge1, edge2));
            rec.cor = cor;
            return true;
        }
        return false;
    }
    return false;
}