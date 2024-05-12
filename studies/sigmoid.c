#include <gmshc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double Sigmoid(double x,double L,double k,double m) {
    double result = L / (1 + exp(-k*(x-m)));
    return result;
}

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


    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);


    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 6, 0, &ierr);

    const int s1[] = {6};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    double x0 = 1.5, x1 = 3, x;
    int nPoints = 15;
    double gap = (x1 - x0) / nPoints;
    x = x0;
    int splinePoints1[nPoints], splinePoints2[nPoints];
    x+=gap;


    double midpoint=2.25,supremum=1.7,steepness=3;

    for (size_t i = 0; i < nPoints; i++) {
        int tag = i + 100;
        gmshModelGeoAddPoint(x, Sigmoid(x,supremum,steepness,midpoint), 0, lc/2, tag, &ierr);
        x += gap;
        splinePoints1[i] = tag;
    }

    gmshModelGeoAddSpline(splinePoints1, nPoints, 101, &ierr);
    gmshModelGeoAddSpline(splinePoints2, nPoints, 102, &ierr);
    gmshModelGeoSynchronize(&ierr);

    int aaa[] = {101,102};

    gmshModelMeshEmbed(1, aaa, 2, 2, 1, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("studies/fracture.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
