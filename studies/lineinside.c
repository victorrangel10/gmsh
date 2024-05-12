#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);
    double lc = 0.1;
    double initial_x = 0, initial_y = 0, height = 2, width = 4;

    gmshModelAdd("t1", &ierr);

    gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y + height, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y + height, 0, lc, 4, &ierr);

    gmshModelGeoAddPoint(1.5, 0.5, 0, lc, 5, &ierr);
    gmshModelGeoAddPoint(3, 1.5, 0, lc, 6, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);

    gmshModelGeoAddLine(5, 6, 5, &ierr);

    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 6, 0, &ierr);

    const int s1[] = {6};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    int aaa[] = {5};
    gmshModelMeshEmbed(1,aaa,1,2,1,&ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("studies/fracture.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
