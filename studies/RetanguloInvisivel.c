#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
    int ierr;

    double lc = .1;

    double initial_x, initial_y, size;

    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("t4", &ierr);

    gmshModelGeoAddPoint(0, 0, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(5, 0, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(5, 3, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(3, 3, 0, lc, 4, &ierr);
    gmshModelGeoAddPoint(3, 2, 0, lc, 5, &ierr);
    gmshModelGeoAddPoint(0, 2, 0, lc, 6, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(2, 3, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 5, 4, &ierr);
    gmshModelGeoAddLine(5, 6, 5, &ierr);
    gmshModelGeoAddLine(6, 1, 6, &ierr);

    double raio = .5;

    double x_center = 4, y_center = 1;

    gmshModelGeoAddPoint(x_center, y_center, 0, lc, 11, &ierr);  // centro

    gmshModelGeoAddPoint(x_center, y_center + raio, 0, lc, 12, &ierr);  // topo

    gmshModelGeoAddPoint(x_center, y_center - raio, 0, lc, 13, &ierr);  // baixo

    gmshModelGeoAddCircleArc(12, 11, 13, 110, 0, 0, 0, &ierr);  // adicionando circulo

    gmshModelGeoAddCircleArc(13, 11, 12, 111, 0, 0, 0, &ierr);  // adicionando circulo

    const int cl2[] = {110, 111};

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);

    const int cl1[] = {1, 2, 3, 4, 5, 6, -110, -111};  // cria curve loop excluindo as curvas do circulo

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    const double pl1[] = {1, 2, 3, 4, 5, 6};

    gmshModelMeshFieldAdd("Distance", 5, &ierr);

    gmshModelMeshFieldSetNumber(5, "Sampling", 50, &ierr);
    gmshModelMeshFieldSetNumbers(5, "CurvesList", pl1, 6, &ierr);

    gmshModelMeshFieldAdd("MathEval", 2, &ierr);

    char expression[100];

    sprintf(expression, "%g + F5*4", lc / 2);

    gmshModelMeshFieldSetString(2, "F", expression, &ierr);

    // retangulo invisivel
    gmshModelMeshFieldAdd("Box", 3, &ierr);

    gmshModelMeshFieldSetNumber(3, "VIn", lc / 5, &ierr);

    gmshModelMeshFieldSetNumber(3, "VOut", lc *2.5, &ierr);

    gmshModelMeshFieldSetNumber(3, "XMin", 0.75, &ierr);

    gmshModelMeshFieldSetNumber(3, "YMin", 0.75, &ierr);

    gmshModelMeshFieldSetNumber(3, "XMax", 2.25, &ierr);

    gmshModelMeshFieldSetNumber(3, "YMax", 1.25, &ierr);

    gmshModelMeshFieldSetNumber(3, "Thickness", 1.5, &ierr);

    gmshModelMeshFieldAdd("Min", 4, &ierr);

    // refinado nas bordas

    double fl[] = {2, 3};

    gmshModelMeshFieldSetNumbers(4, "FieldsList", fl, 2, &ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(4, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("retanguloinvi.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
