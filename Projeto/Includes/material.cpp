#include "./material.h"

material::material() {}

material::material(float ckd,float cka,float cks,float ckr,float ckt,float cn)
{
    n = cn;
    // normalizacao dos coeficientes
    // kd : difuso
    if (ckd > 1) kd = 1;
    else if (ckd < 0) kd = 0;
    else kd = ckd;

    // ka : ambiental
    if (cka > 1) ka = 1;
    else if (cka < 0) ka = 0;
    else ka = cka;

    // ks : especular
    if (cks > 1) ks = 1;
    else if (cks < 0) ks = 0;
    else ks = cks;

    // kr : reflexao
    if (ckr > 1) kr = 1;
    else if (ckr < 0) kr = 0;
    else kr = ckr;

    // kt : transmissao
    if (ckt > 1) kt = 1;
    else if (ckt < 0) kt = 0;
    else kt = ckt;
}
