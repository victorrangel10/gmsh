#include <gmshc.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("square", &ierr);

    const double lc = 0.01;

    gmshModelGeoAddPoint(.2, 0, 0, lc, 1, &ierr);

    // a malha fica mais refinada nesse ponto
    gmshModelGeoAddPoint(-.2, 0, 0, lc/5, 2, &ierr);

    // a malha fica mais espaçada nesse ponto
    gmshModelGeoAddPoint(.2, .2, 0, lc*10, 3, &ierr);
    
    gmshModelGeoAddPoint(-.2, .2, 0, lc, 4, &ierr);


    gmshModelGeoAddLine(1,2,1,&ierr);
    gmshModelGeoAddLine(2,4,2,&ierr);
    gmshModelGeoAddLine(4,3,3,&ierr);
    gmshModelGeoAddLine(3,1,4,&ierr);
    const int cl1[] = {1,2, 3, 4};

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};

    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("squaretest.msh", &ierr);


    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    
    return 0;

}