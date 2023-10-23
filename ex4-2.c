#include <stdio.h>

#include "gmshc.h"

int main(int argc, char** argv) {
    const double lc = 1e-2;

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

    double raio=0.03; //comecando a circunferencia

    gmshModelGeoAddPoint(0.05, 0.04, 0, lc, 11, &ierr); // centro

    gmshModelGeoAddPoint(0.05, 0.04+raio, 0, lc, 12, &ierr); // topo

    gmshModelGeoAddPoint(0.05, 0.04-raio, 0, lc, 13, &ierr); // baixo


    gmshModelGeoAddCircleArc(12,11,13,110,0,0,0,&ierr); // adicionando circulo 
    

    gmshModelGeoAddCircleArc(13,11,12,111,0,0,0,&ierr); // adicionando circulo 


    const int cl2[] = {110,111};

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);


    const int cl1[] = {4, 1, -2, 3,-110,-111}; // cria curve loop excluindo as curvas do circulo

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshFieldAdd("Distance", 1, &ierr);  // cria campo para adicionar o circulo

    const double pl1[] = {110,111};

    gmshModelMeshFieldSetNumbers(1, "CurvesList", pl1, 2, &ierr);  // bota  os semicirculos como pertecentes ao campo


    gmshModelMeshFieldSetNumber(1, "Sampling", 20, &ierr); // determina o numero de pontos computados 
    //na linha, quanto mais pontos, mais refinado fica

    gmshModelMeshFieldAdd("Threshold", 2, &ierr);

    gmshModelMeshFieldSetNumber(2, "InField", 1, &ierr);

    gmshModelMeshFieldSetNumber(2, "SizeMin", lc / 5, &ierr); // determina size para elementos mais perto do ponto

    gmshModelMeshFieldSetNumber(2, "SizeMax", lc/2, &ierr); // determina size para elementos mais distantes do ponto

    gmshModelMeshFieldSetNumber(2, "DistMin", 0.0015, &ierr);

    gmshModelMeshFieldSetNumber(2, "DistMax", 0.00151, &ierr);

    gmshModelMeshFieldAdd("Min",3,&ierr);

    double fl[]={1,2};


    gmshModelMeshFieldSetNumbers(3,"FieldsList",fl,2,&ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(3,&ierr);


    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("ex4-2.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}