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

    gmshModelAdd("m1", &ierr);

    gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + width, initial_y + height, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y + height, 0, lc, 4, &ierr);

    int pointTag = 4;

    srand(time(NULL));

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);
    int lineTag = 4;
    int splineTag = 100;
    // Criando spline

    double x1, x2, x3, x4, y1, y2, y3, y4;
    printf("Selecione o numero de fraturas splines: \n");
    int nFracSpline;
    scanf("%d", &nFracSpline);

    int fractureSpline[nFracSpline];
    for (size_t i = 0; i < nFracSpline; i++) {
        x1 = random_double(initial_x + 0.2, width - 0.2);  // de 0.2 ate a metade da largura

        x2 = random_double(initial_x + 0.2, width - 0.2);  // pode ir do primeiro ponto ate o final do retangulo

        y1 = random_double(initial_y + 0.2, height - 0.2);  // de 0.2 ate a metade da altura

        y2 = random_double(initial_y + 0.2, height - 0.2);

        x3 = random_double(initial_x + 0.2, width - 0.2);  // de 0.2 ate a metade da largura

        x4 = random_double(initial_x + 0.2, width - 0.2);  // pode ir do primeiro ponto ate o final do retangulo

        y3 = random_double(initial_y + 0.2, height - 0.2);  // de 0.2 ate a metade da altura

        y4 = random_double(initial_y + 0.2, height - 0.2);

        pointTag += 4;
        splineTag++;
        GeraSpline(x1, y1, x2, y2, x3, y3, x4, y4, pointTag, splineTag, ierr, lc);
    
        fractureSpline[i] = splineTag;
        
    }

    // CRIANDO RETA
    double x5, x6, y5, y6;

    printf("Selecione o numero de fraturas lineares: \n");
    int nFracLin;
    scanf("%d", &nFracLin);

    int fractureLin[nFracLin];

    for (size_t i = 0; i < nFracLin; i++) {
        x5 = random_double(initial_x + 0.2, width / 2);  // de 0.2 ate a metade da largura

        x6 = random_double(x5, width - 0.2);  // pode ir do primeiro ponto ate o final do retangulo

        y5 = random_double(initial_y + 0.2, height / 2);  // de 0.2 ate a metade da altura
        y6 = random_double(y5, height);
        printf("oiii");
        pointTag += 2;
        lineTag++;
        GeraLinha(x5, y5, x6, y6, pointTag, lc, ierr, lineTag);

        fractureLin[i] = lineTag;
    }

 
    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 6, 0, &ierr);

    const int s1[] = {6};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshEmbed(1, fractureSpline, nFracSpline, 2, 1, &ierr);

    gmshModelMeshEmbed(1, fractureLin, nFracLin, 2, 1, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("exerciciosBenchmark/studies/randomfracture.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);

    return 0;
}
