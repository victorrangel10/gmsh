#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

void GeraLinha(double x1, double y1, double x2, double y2, int startTag, double lc, int ierr, int linhaTag) {
    gmshModelGeoAddPoint(x1, y1, 0, lc, startTag, &ierr);
    gmshModelGeoAddPoint(x2, y2, 0, lc, startTag + 1, &ierr);
    gmshModelGeoAddLine(startTag, startTag + 1, linhaTag, &ierr);
}

int main(int argc, char** argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);
    double lc = 0.1;
    double initial_x = 0, initial_y = 0, height = 2, width = 4;
    srand(time(NULL));
    gmshModelAdd("m1", &ierr);

    // gerando retangulo
    gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y + height, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y + height, 0, lc, 4, &ierr);
    int lastPointTag = 4;

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);
    int lastLineTag = 4;

    // gerando fraturas
    printf("Selecione o numero de fraturas: \n");
    int nFrac;
    scanf("%d", &nFrac);
    double x2, x1, y2, y1;

    int fracture[nFrac];
  
    for (size_t i = 0; i < nFrac; i++) {
        x1 = random_double(initial_x + 0.2, width / 2);  // de 0.2 ate a metade da largura

        x2 = random_double(x1, width - 0.2);  // pode ir do primeiro ponto ate o final do retangulo

        y1 = random_double(initial_y + 0.2, height / 2);  // de 0.2 ate a metade da altura

        y2 = random_double(y1, height);
        printf("Ponto %d gerado, (%.2f , %.2f)", i, x1, y1);
        printf("Ponto %d gerado, (%.2f , %.2f)", i + 1, x2, y2);

        lastPointTag+=2;
        lastLineTag++;
        GeraLinha(x1, y1, x2, y2, lastPointTag, lc, ierr, lastLineTag);

        fracture[i] = lastLineTag;
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
