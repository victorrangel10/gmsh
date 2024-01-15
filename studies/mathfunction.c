#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int ierr;

    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("square", &ierr);

    const double lc = 1;
    // adicionando pontos para montar um quadrado
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

    gmshModelGeoSynchronize(&ierr);

    //adicionando campo que computa a distancia dos elementos aos pontos  1 e 2 
    gmshModelMeshFieldAdd("Distance", 1, &ierr);

    double pl1[] = {1, 2};

    gmshModelMeshFieldSetNumbers(1, "PointsList", pl1, 2, &ierr);


    // adicionando um campo que cria uma expressao matemática com os resultados do campo acima
    gmshModelMeshFieldAdd("MathEval", 2, &ierr);

    char expression[100];

    char expression2[100];

    sprintf(expression, "%g + F1", lc / 100);

    sprintf(expression2, "Sin(x*5)*Cos(y*5)");

    printf("Expressao formatada: %s\n", expression);

    gmshModelMeshFieldSetString(2, "F", expression2, &ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(2, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshOptionSetNumber("Mesh.MshFileVersion", 2.2, &ierr); // seleciono a versao do arquivo .msh

    gmshWrite("expression.msh", &ierr);
    gmshFltkRun(&ierr);
    gmshFinalize(&ierr);
    return 0;
}