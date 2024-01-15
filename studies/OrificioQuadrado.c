#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int ierr;
    

    gmshModelAdd("model", &ierr);

    const double lc = 0.5;

    gmshModelGeoAddPoint(0, 0, 0, lc, 1, &ierr);

    gmshModelGeoAddPoint(5, 0, 0, lc, 2, &ierr);

    gmshModelGeoAddPoint(5, 2, 0, lc, 3, &ierr);

    gmshModelGeoAddPoint(4, 3, 0, lc, 4, &ierr);

    gmshModelGeoAddPoint(0, 3, 0, lc, 5, &ierr);

    gmshModelGeoAddPoint(1, 1, 0, lc, 6, &ierr);

    gmshModelGeoAddPoint(1, 2, 0, lc, 7, &ierr);

    gmshModelGeoAddPoint(2, 2, 0, lc, 8, &ierr);

    gmshModelGeoAddPoint(2, 1, 0, lc, 9, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);

    gmshModelGeoAddLine(2, 3, 2, &ierr);

    gmshModelGeoAddLine(3, 4, 3, &ierr);

    gmshModelGeoAddLine(4, 5, 4, &ierr);

    gmshModelGeoAddLine(5, 1, 5, &ierr);

    const int cl1[] = {1, 2, 3, 4, 5};

    gmshModelGeoAddLine(6, 9, 6, &ierr);

    gmshModelGeoAddLine(9, 8, 7, &ierr);

    gmshModelGeoAddLine(8, 7, 8, &ierr);

    gmshModelGeoAddLine(7, 6, 9, &ierr);

    const int cl2[] = {6, 7, 8, 9};

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);

    const int s1[] = {1, -2};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);


    const double op[] = {6, 7, 8, 9};
    gmshModelGeoSynchronize(&ierr);

    // Definir o campo de tamanho (size field)
    gmshModelMeshFieldAdd("Distance", 1, &ierr);

    gmshModelMeshFieldSetNumbers(1, "CurvesList", op,4, &ierr);

    gmshModelMeshFieldSetNumber(1, "Sampling", 10, &ierr);

    gmshModelMeshFieldAdd("Threshold", 2, &ierr);

    gmshModelMeshFieldSetNumber(2, "InField", 1, &ierr);

    gmshModelMeshFieldSetNumber(2, "SizeMin", 0.06, &ierr);  // determina size para elementos mais perto do ponto

    gmshModelMeshFieldSetNumber(2, "SizeMax", 0.08, &ierr);  // determina size para elementos mais distantes do ponto

    gmshModelMeshFieldSetNumber(2, "DistMin", .1, &ierr);

    gmshModelMeshFieldSetNumber(2, "DistMax", 2, &ierr);

    gmshModelMeshFieldAdd("Min", 3, &ierr);

    double fl[] = {1, 2};

    gmshModelMeshFieldSetNumbers(3, "FieldsList", fl, 2, &ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(3, &ierr);

    // Aplicar o campo de tamanho à malha
    gmshModelMeshFieldSetAsBackgroundMesh(1, &ierr);

    // Aplicar o campo de tamanho à malha
    gmshModelMeshFieldSetAsBackgroundMesh(1, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
