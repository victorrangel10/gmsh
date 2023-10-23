#include <stdio.h>

#include "gmshc.h"

int main(int argc, char** argv) {
    const double lc = 1e-2/2;

    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("t1", &ierr);

    gmshModelGeoAddPoint(0, 0, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(.1, 0, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(.1, .1, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(0, .1, 0, lc, 4, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);

    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshFieldAdd("Constant", 1, &ierr); // cria campo para adicionar os 4 pontos

    const double pl1[] = {4, 1,2, 3};

    gmshModelMeshFieldSetNumbers(1, "PointsList", pl1, 4, &ierr); // diz a lista de pontos que estarao no campo

    gmshModelMeshFieldSetNumber(1, "VIn", lc /10, &ierr); // diz o tamanho do meshsize para os pontos

    gmshModelMeshFieldSetAsBackgroundMesh(1, &ierr); // seta o field criado como background mesh



    //gmshOptionSetNumber("Mesh.MeshSizeExtendFromBoundary", 0, &ierr);

    //gmshOptionSetNumber("Mesh.MeshSizeFromPoints", 0, &ierr);

    //gmshOptionSetNumber("Mesh.MeshSizeFromCurvature", 0, &ierr);

    //gmshOptionSetNumber("Mesh.Algorithm", 5, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("ex1.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}