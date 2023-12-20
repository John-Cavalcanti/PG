#include "./plane.h"
#include "../Tools/MatrixOperations.h"
#include "../Tools/Matrix4X4.h"
bool plane::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    float t = glm::dot((plane_point - r.location()), normal) / glm::dot(r.direction(), normal);

    if(t < t_max && t > t_min){
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = normal;
        rec.cor = cor;
        return true;
    }
    return false;
}

void plane::translade(float x, float y, float z) {
    Matrix4X4 translationMatrix;
    translationMatrix.toTranslationMatrix(x, y, z);
    plane_point = pointMatrixMultiplication(plane_point.x, plane_point.y, plane_point.z, translationMatrix);
}

void plane::rotate(double angle, char axis) {
    Matrix4X4 rotationMatrix;
    rotationMatrix.toRotationMatrix(angle, axis);
    normal = vectorMatrixMultiplication(normal.x, normal.y, normal.z, rotationMatrix);
}