#include <stdio.h>

#include "gmshc.h"
#include <stdlib.h>

int main(int argc, char** argv) {
    int ierr;

    double lc;

    printf("Select global mesh size\n");

    scanf("%lf", &lc);

    printf("Select square inital coordinates(x,y) and side size\n");

    double initial_x, initial_y, size;

    if (scanf("%lf %lf %lf", &initial_x, &initial_y, &size) != 3) {
        exit(1);
    }

    
    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("t4", &ierr);

    gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y + size, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y + size, 0, lc, 4, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);

    double raio = 0.03;  // comecando a circunferencia

    printf("Select circle radius\n");
    scanf("%lf", &raio);

    printf("Select circle center coordinates\n");

    double x_center, y_center;

    if (scanf("%lf %lf", &x_center, &y_center) != 2) {
        exit(1);
    }

 /*   while (!(x_center + raio > initial_x + size || x_center - raio < initial_x || y_center + raio > initial_y + size || y_center - raio < initial_y)) {
        printf("The circle extrapolated the square limits, insert new center coordinates\n");
        if (scanf("%lf %lf", &x_center, &y_center) != 2) {
            exit(1);
        }
    }*/

    gmshModelGeoAddPoint(x_center, y_center, 0, lc, 11, &ierr);  // centro

    gmshModelGeoAddPoint(x_center, y_center + raio, 0, lc, 12, &ierr);  // topo

    gmshModelGeoAddPoint(x_center, y_center - raio, 0, lc, 13, &ierr);  // baixo

    gmshModelGeoAddCircleArc(12, 11, 13, 110, 0, 0, 0, &ierr);  // adicionando circulo

    gmshModelGeoAddCircleArc(13, 11, 12, 111, 0, 0, 0, &ierr);  // adicionando circulo

    const int cl2[] = {110, 111};

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);

    const int cl1[] = {4, 1, -2, 3, -110, -111};  // cria curve loop excluindo as curvas do circulo

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("ex4.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}