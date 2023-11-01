//MESMA COIA DO SEGUNDO EXEMPLO, POREM USANDO UM FIELD DO TIPO DISTANCE

#include <stdio.h>

#include "gmshc.h"

int main(int argc, char** argv) {
    const double lc = (1e-2) ;

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


    gmshModelGeoAddPoint(.1, .05, 0, lc, 5, &ierr); // criando ponto para ser centro do semicirculo

    gmshModelGeoAddCircleArc(2,5,3,11,0,0,0,&ierr); // adicionando arco de circulo 

    const int cl2[] = {2,11}; // adicionando nova superficie (semicirculo)

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);

    const int s2[] = {2};

    gmshModelGeoAddPlaneSurface(s2, sizeof(s2) / sizeof(s2[0]), 2, &ierr); // adicionado

    gmshModelGeoSynchronize(&ierr);

    //gmshOptionSetNumber("Mesh.Algorithm", 5, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("ex5.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}