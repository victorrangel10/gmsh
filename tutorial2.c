#include <gmshc.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("t1", &ierr);

    const double lc = 0.01;

    gmshModelGeoAddPoint(0, 0, 0, lc, 1, &ierr);

    gmshModelGeoAddPoint(.8, .5, 0, lc, 2, &ierr);

    gmshModelGeoAddPoint(.1, .8, 0, lc, 3, &ierr);

    gmshModelGeoAddPoint(.1, .3, 0, lc, 4, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);

    gmshModelGeoAddLine(2, 3, 2, &ierr);

    gmshModelGeoAddLine(3, 4, 3, &ierr);

    gmshModelGeoAddLine(4, 1, 4, &ierr);

    const int cl1[] = {1, 2, 3, 4};

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};

    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);  // mesma coisa do primeiro codigo

    // adicionando pontos acima dos pontos que ja existem para criar um volume

    gmshModelGeoAddPoint(0, 0, .5, lc, 5, &ierr);

    gmshModelGeoAddPoint(.8, .5, .5, lc, 6, &ierr);

    gmshModelGeoAddPoint(.1, .8, .5, lc, 7, &ierr);

    gmshModelGeoAddPoint(.1, .3, .5, lc, 8, &ierr);

    // conectando os pontos de baixo aos de cima com linhas

    gmshModelGeoAddLine(1, 5, 101, &ierr);
    gmshModelGeoAddLine(2, 6, 102, &ierr);
    gmshModelGeoAddLine(3, 7, 103, &ierr);
    gmshModelGeoAddLine(4, 8, 104, &ierr);

    // fechando o quadrilatero superior

    gmshModelGeoAddLine(5, 6, 105, &ierr);
    gmshModelGeoAddLine(6, 7, 106, &ierr);
    gmshModelGeoAddLine(7, 8, 107, &ierr);
    gmshModelGeoAddLine(8, 5, 108, &ierr);

    // adicionando curve loops

    const int cl3[] = {101, 102, 1, 105};  // base
    gmshModelGeoAddCurveLoop(cl3, sizeof(cl3) / sizeof(cl3[0]), 3, 0, &ierr);
    const int s3[] = {3};
    gmshModelGeoAddPlaneSurface(s3, sizeof(s3) / sizeof(s3[0]), 3, &ierr);

    const int cl4[] = {102, 106, 103, 2};  // "parede direita "
    gmshModelGeoAddCurveLoop(cl4, sizeof(cl4) / sizeof(cl4[0]), 4, 0, &ierr);
    const int s4[] = {4};
    gmshModelGeoAddPlaneSurface(s4, sizeof(s4) / sizeof(s4[0]), 4, &ierr);

    const int cl5[] = {105, 108, 107, 106};  //"seta traseira"
    gmshModelGeoAddCurveLoop(cl5, sizeof(cl5) / sizeof(cl5[0]), 5, 0, &ierr);
    const int s5[] = {5};
    gmshModelGeoAddPlaneSurface(s5, sizeof(s5) / sizeof(s5[0]), 5, &ierr);

    const int cl6[] = {103, 107, 104, 3};  //"fold de cima"
    gmshModelGeoAddCurveLoop(cl6, sizeof(cl6) / sizeof(cl6[0]), 6, 0, &ierr);
    const int s6[] = {6};
    gmshModelGeoAddPlaneSurface(s6, sizeof(s6) / sizeof(s6[0]), 6, &ierr);

    const int cl7[] = {101, 108, 4, 104};  //"fold  de baixo"
    gmshModelGeoAddCurveLoop(cl7, sizeof(cl7) / sizeof(cl7[0]), 7, 0, &ierr);
    const int s7[] = {7};
    gmshModelGeoAddPlaneSurface(s7, sizeof(s7) / sizeof(s7[0]), 7, &ierr);

    const int sl1[] = {1, 3, 4, 5, 6, 7};
    gmshModelGeoAddSurfaceLoop(sl1, sizeof(sl1) / sizeof(sl1[0]), 201, &ierr); //loop dos lados do volume

    const int v1[] = {201};
    gmshModelGeoAddVolume(v1, sizeof(v1) / sizeof(v1[0]), 301, &ierr); // criacao do volume a partir do loop
    //
    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshGenerate(3, &ierr);

    gmshWrite("tutorial2.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
