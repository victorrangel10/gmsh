

#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int ierr;

    double lc;

    printf("Select mesh size\n");

    scanf("%lf", &lc);

    printf("Select square inital coordinates(x,y) and side size\n");

    double initial_x, initial_y, size;

    if (scanf("%lf %lf %lf", &initial_x, &initial_y, &size) != 3) {
        exit(1);
    }
    gmshInitialize(argc, argv, 1, 0, &ierr);

     printf("Select square mesh orientation (Left/Right)\n");

    char orientation[10];

    scanf("%s",orientation);


    gmshModelAdd("t1", &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y + size, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y + size, 0, lc, 4, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);

    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoAddPoint(initial_x+size, initial_y+(size/2), 0, lc, 5, &ierr);  // criando ponto para ser centro do semicirculo

    gmshModelGeoAddCircleArc(2, 5, 3, 11, 0, 0, 0, &ierr);  // adicionando arco de circulo

    const int cl2[] = {2, 11};  // adicionando nova superficie (semicirculo)

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);

    const int s2[] = {2};

    gmshModelGeoAddPlaneSurface(s2, sizeof(s2) / sizeof(s2[0]), 2, &ierr);  // adicionado

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshSetTransfiniteCurve(1, 20, "Progression", 1.0, &ierr);

    gmshModelMeshSetTransfiniteCurve(2, 20, "Progression", 1.0, &ierr);

    gmshModelMeshSetTransfiniteCurve(3, 20, "Progression", 1.0, &ierr);

    gmshModelMeshSetTransfiniteCurve(4, 20, "Progression", 1.0, &ierr);

    const int ts[] = {1, 2, 3, 4};

    // mudar argumento para Left ou Right para trocar o tipo de padrao
    gmshModelGeoMeshSetTransfiniteSurface(1, "orientation", ts, 4, &ierr);

    // gmshOptionSetNumber("Mesh.Algorithm", 5, &ierr);

    gmshOptionSetNumber("Mesh.Smoothing", 100, &ierr);
    gmshModelGeoSynchronize(&ierr);
    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("exerciciosBenchmark/QuadradoComSemicirculo/quadradoComSemicirculo.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
