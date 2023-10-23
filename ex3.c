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

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshSetTransfiniteCurve(1, 20, "Progression", 1.0, &ierr);

    gmshModelMeshSetTransfiniteCurve(2, 20, "Progression", 1.0, &ierr);

    gmshModelMeshSetTransfiniteCurve(3, 20, "Progression", 1.0, &ierr);

    gmshModelMeshSetTransfiniteCurve(4, 20, "Progression", 1.0, &ierr);

    const int ts[] = {1, 2, 3, 4};


    //mudar argumento para Left ou Right para trocar o tipo de padrao
    gmshModelGeoMeshSetTransfiniteSurface(1, "AlternateLeft", ts, 4, &ierr);

    gmshOptionSetNumber("Mesh.Smoothing", 100, &ierr);

    gmshModelGeoSynchronize(&ierr);
    gmshModelMeshGenerate(2, &ierr);
    gmshWrite("ex3.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}