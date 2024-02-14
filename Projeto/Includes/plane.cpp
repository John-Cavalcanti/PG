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

        // informacoes sobre o material do objeto
        rec.kdif = objMaterial->kd;
        rec.kamb = objMaterial->ka;
        rec.kespc = objMaterial->ks;
        rec.rug = objMaterial->n;

        // info dos materiais para a entraga 5, no momento da entrega 4 usaremos os valores 0
        rec.kref = objMaterial->kr;
        rec.ktrans = objMaterial->kt;
        return true;
    }
    return false;
}

void plane::translade(float x, float y, float z) {
    Matrix4X4 translationMatrix; //Esta linha cria uma nova instância da classe Matrix4X4 chamada translationMatrix. Inicialmente, esta é uma matriz de identidade.
    translationMatrix.toTranslationMatrix(x, y, z);// Isso modifica a translationMatrix para ser uma matriz de translação que representa um movimento de x unidades ao longo do eixo x, y unidades ao longo do eixo y e z unidades ao longo do eixo z.
    plane_point = pointMatrixMultiplication(plane_point.x, plane_point.y, plane_point.z, translationMatrix);//Multiplica o ponto por uma matriz
    //O ponto é especificado pelas coordenadas plane_point.x, plane_point.y e plane_point.z, e a matriz é a translationMatrix. O resultado da multiplicação é atribuído de volta a plane_point.
}

void plane::rotate(double angle, char axis) {
    Matrix4X4 rotationMatrix; //Esta linha cria uma nova instância da classe Matrix4X4 chamada translationMatrix. Inicialmente, esta é uma matriz de identidade.
    rotationMatrix.toRotationMatrix(angle, axis);//Isso modifica a rotationMatrix para ser uma matriz de rotação que representa uma rotação de angle graus em torno do eixo axis.
    normal = vectorMatrixMultiplication(normal.x, normal.y, normal.z, rotationMatrix);// Multiplica o vetor normal por uma matriz de rotacao. O vetor é especificado pelas coordenadas normal.x, normal.y e normal.z, e a matriz é a rotationMatrix. O resultado da multiplicação é atribuído de volta a normal. 
}