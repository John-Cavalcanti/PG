#include "./spheres.h"
#include "../Tools/MatrixOperations.h"
#include "../Tools/Matrix4X4.h"
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.location() - center; // vetor que vai do centro da esfera até a origem do raio
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius; // calcula o dot product de oc com ele mesmo, e subtrai o raio ao quadrado
    //a, b e c são os coeficientes da equação de segundo grau
    float discriminant = b*b - a*c;
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.cor = cor;

            rec.kdif = objMaterial->kd;
            rec.kamb = objMaterial->ka;
            rec.kespc = objMaterial->ks;
            rec.rug = objMaterial->n;

            rec.kref = objMaterial->kr;
            rec.ktrans = objMaterial->kt;

            return true;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.cor = cor;

            rec.kdif = objMaterial->kd;
            rec.kamb = objMaterial->ka;
            rec.kespc = objMaterial->ks;
            rec.rug = objMaterial->n;

            rec.kref = objMaterial->kr;
            rec.ktrans = objMaterial->kt;
            
            return true;
        }
    }
    
    return false;
}
void sphere::translade(float x, float y, float z) {
    /* 
    Este método translada (move) o centro da esfera ao longo dos eixos x, y e z. 
    Ele cria uma matriz de translação usando os valores x, y e z fornecidos e, em seguida, multiplica o ponto central da esfera por essa matriz de translação. 
    O resultado é um novo ponto central que foi transladado pelas quantidades x, y e z.
    */
    Matrix4X4 translationMatrix;
    translationMatrix.toTranslationMatrix(x, y, z);
    center = pointMatrixMultiplication(center.x, center.y, center.z, translationMatrix);
}

void sphere::rotate(double angle, char axis) {

    /*
        Este método rotaciona o centro da esfera em torno de um eixo específico por um ângulo específico.
        Ele cria uma matriz de rotação usando o ângulo e o eixo fornecidos e, em seguida, multiplica o ponto central da esfera por essa matriz de rotação.
        O resultado é um novo ponto central que foi rotacionado pelo ângulo angle em torno do eixo axis.
    */
    Matrix4X4 rotationMatrix;
    rotationMatrix.toRotationMatrix(angle, axis);
    center = pointMatrixMultiplication(center.x, center.y, center.z, rotationMatrix);
}