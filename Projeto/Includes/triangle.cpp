#include "./triangle.h"

bool triangle::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    float t = glm::dot((a - r.location()), normal) / glm::dot(r.direction(), normal);

    if (t < t_max && t > t_min)
    {
        // Ponto de interseção com o plano:
        glm::vec3 p = r.point_at_parameter(t);
        
        // Vetor do vertice do triangulo até o ponto p
        glm::vec3 w = p - a;
        
        float beta = glm::dot(w, hb);
        float gamma = glm::dot(w, hc);
        float alpha = 1 - beta - gamma;

        if (alpha >= 0 && beta >= 0 && gamma >= 0)
        {
            rec.t = t;
            rec.p = p;
            rec.normal = normal;
            rec.cor = cor;
            return true;
        }
        return false;
    }
    return false;
}