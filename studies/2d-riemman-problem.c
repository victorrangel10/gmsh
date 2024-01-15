#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ierr;

    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("square", &ierr);

    const double lc = 0.05;

    gmshModelGeoAddPoint(0, 0, 0, lc, 1, &ierr);

    gmshModelGeoAddPoint(1, 0, 0, lc, 2, &ierr);

    gmshModelGeoAddPoint(0, 1, 0, lc, 3, &ierr);

    gmshModelGeoAddPoint(1, 1, 0, lc, 4, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);

    gmshModelGeoAddLine(2, 4, 2, &ierr);

    gmshModelGeoAddLine(4, 3, 3, &ierr);

    gmshModelGeoAddLine(3, 1, 4, &ierr);

    const int cl1[] = {1, 2, 3, 4};

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};

    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    // linha vertical
    gmshModelMeshFieldAdd("Box", 1, &ierr);

    gmshModelMeshFieldSetNumber(1, "VIn", lc / 5, &ierr);

    gmshModelMeshFieldSetNumber(1, "VOut", lc, &ierr);

    gmshModelMeshFieldSetNumber(1, "XMin", 0.59, &ierr);

    gmshModelMeshFieldSetNumber(1, "YMin", 0, &ierr);

    gmshModelMeshFieldSetNumber(1, "XMax", 0.61, &ierr);

    gmshModelMeshFieldSetNumber(1, "YMax", 1, &ierr);

    gmshModelMeshFieldSetNumber(1, "Thickness", 0.25, &ierr);

    gmshModelGeoSynchronize(&ierr);

    // linha horizontal
    gmshModelMeshFieldAdd("Box", 2, &ierr);

    gmshModelMeshFieldSetNumber(2, "VIn", lc / 5, &ierr);

    gmshModelMeshFieldSetNumber(2, "VOut", lc * 2.5, &ierr);

    gmshModelMeshFieldSetNumber(2, "XMin", 0, &ierr);

    gmshModelMeshFieldSetNumber(2, "YMin", 0.55, &ierr);

    gmshModelMeshFieldSetNumber(2, "XMax", 1, &ierr);

    gmshModelMeshFieldSetNumber(2, "YMax", 0.57, &ierr);

    gmshModelMeshFieldSetNumber(2, "Thickness", 0.25, &ierr);

    gmshModelMeshFieldAdd("Min", 4, &ierr);

    double fl[] = {1,2};

    gmshModelMeshFieldSetNumbers(4, "FieldsList", fl, 2, &ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(4, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("2d-riemman.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
