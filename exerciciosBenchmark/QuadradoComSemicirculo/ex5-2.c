

#include <stdio.h>

#include "gmshc.h"

int main(int argc, char** argv) {
    const double lc = (1e-2)*10 ;

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


    gmshModelGeoAddPoint(.1, .05, 0, lc, 5, &ierr);

    gmshModelGeoAddCircleArc(2,5,3,11,0,0,0,&ierr);

    const int cl2[] = {2,11};

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);

    const int s2[] = {2};

    gmshModelGeoAddPlaneSurface(s2, sizeof(s2) / sizeof(s2[0]), 2, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshFieldAdd("Distance", 1, &ierr);  // ria campo para adicionar a reta

    const double pl1[] = {2};

    gmshModelMeshFieldSetNumbers(1, "CurvesList", pl1, 1, &ierr);  // bota  a reta como pertecente ao campo

    gmshModelMeshFieldSetNumber(1, "Sampling", 100, &ierr); // determina o numero de pontos computados 
    //na linha, quanto mais pontos, mais refinado fica

    gmshModelMeshFieldAdd("Threshold", 2, &ierr);

    gmshModelMeshFieldSetNumber(2, "InField", 1, &ierr); // seleciona o field que esta dando os valores a serem computados

    gmshModelMeshFieldSetNumber(2, "SizeMin", lc / 10, &ierr); // determina size para elementos mais perto do ponto

    gmshModelMeshFieldSetNumber(2, "SizeMax", lc, &ierr); // determina size para elementos mais distantes do ponto

    gmshModelMeshFieldSetNumber(2, "DistMin", 0.15, &ierr);

    gmshModelMeshFieldSetNumber(2, "DistMax", 0.5, &ierr);

    gmshModelMeshFieldAdd("Min",3,&ierr);

    double fl[]={1,2};

    gmshModelMeshFieldSetNumbers(3,"FieldsList",fl,2,&ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(3,&ierr);

     gmshOptionSetNumber("Mesh.MeshSizeExtendFromBoundary", 0, &ierr);

     gmshOptionSetNumber("Mesh.MeshSizeFromPoints", 0, &ierr);

     gmshOptionSetNumber("Mesh.MeshSizeFromCurvature", 0, &ierr);

     gmshOptionSetNumber("Mesh.Algorithm", 5, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("ex5-2.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
