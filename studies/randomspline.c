#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void GeraSpline(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, int pointTag, int splineTag, int ierr, double lc) {
    gmshModelGeoAddPoint(x1, y1, 0, lc, pointTag, &ierr);
    gmshModelGeoAddPoint(x2, y2, 0, lc, pointTag + 1, &ierr);
    gmshModelGeoAddPoint(x3, y3, 0, lc, pointTag + 2, &ierr);
    gmshModelGeoAddPoint(x4, y4, 0, lc, pointTag + 3, &ierr);

    int splinePoints[4] = {pointTag, pointTag + 1, pointTag + 2, pointTag + 3};

    gmshModelGeoAddSpline(splinePoints, 4, splineTag, &ierr);
}

int main(int argc, char** argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);
    double lc = 0.1;
    double initial_x = 0, initial_y = 0, height = 2, width = 4;

    gmshModelAdd("m1", &ierr);

    gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y + height, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y + height, 0, lc, 4, &ierr);
    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);
    int pointTag = 4;
    double x4, x3, x2, x1, y4, y3, y2, y1;
    int splineTag = 20;

    srand(time(NULL));
    printf("Selecione o numero de fraturas: \n");
    int nFrac;
    scanf("%d", &nFrac);

    int fracture[nFrac];
    for (size_t i = 0; i < nFrac; i++) {
        x1 = random_double(initial_x + 0.2, width - 0.2);  // de 0.2 ate a metade da largura

        x2 = random_double(initial_x + 0.2, width - 0.2);  // pode ir do primeiro ponto ate o final do retangulo

        y1 = random_double(initial_y + 0.2, height - 0.2);  // de 0.2 ate a metade da altura

        y2 = random_double(initial_y + 0.2, height - 0.2);

        x3 = random_double(initial_x + 0.2, width - 0.2);  // de 0.2 ate a metade da largura

        x4 = random_double(initial_x + 0.2, width - 0.2);  // pode ir do primeiro ponto ate o final do retangulo

        y3 = random_double(initial_y + 0.2, height - 0.2);  // de 0.2 ate a metade da altura

        y4 = random_double(initial_y + 0.2, height - 0.2);

        pointTag++;
        GeraSpline(x1, y1, x2, y2, x3, y3, x4, y4, pointTag, splineTag, ierr, lc);
        pointTag += 3;
        fracture[i] = splineTag;
        splineTag++;
    }

    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 6, 0, &ierr);

    const int s1[] = {6};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshEmbed(1, fracture, nFrac, 2, 1, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("exerciciosBenchmark/studies/randomfracture.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);

    return 0;
}
