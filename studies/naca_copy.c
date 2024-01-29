#include <gmshc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("naca", &ierr);

    const double lc = 1;

    double x = 0, t = 0.12;
    int i = 0;

    float jump =0.5;
    // criando os pontos de cima
    for (x = 0; x < 1.01; x += jump) {
        i++;
        // definindo funcao
        double y = 5 * t * ((0.2969 * sqrt(x)) - (0.1260 * x) - (0.3516 * x * x) + (0.2843 * x * x * x) - (0.1015 * pow(x, 4)));
        printf("criando ponto %d, x vale %f e y %f\n", i, x, y);
        gmshModelGeoAddPoint(x, y, 0, lc, i, &ierr);
    }

    int upperPoints = i;  // obtem o numero de pontos que ja foram

    // criando os pontos de baixo
    i = 0;
    for (x = 1; x >0.00; x -= jump) {
        i++;
        double y = -1 * 5 * t * ((0.2969 * sqrt(x)) - (0.1260 * x) - (0.3516 * x * x) + (0.2843 * x * x * x) - (0.1015 * pow(x, 4)));
        printf("criando ponto %d, x vale %f e y %f\n", i + upperPoints, x, y);
        gmshModelGeoAddPoint(x, y, 0, lc, i + upperPoints, &ierr);
    }
    int lastPoint = i + upperPoints;
    int k;
    printf("upperpoints eh %d\n",upperPoints);
    // criando as linhas de cima

    for (k = 1; k < upperPoints; k++) {
        gmshModelGeoAddLine(k, k + 1, k, &ierr);
        printf("linha %d conecta pontos %d e %d\n", k, k, k + 1);
    }

    int upperLines = k-1;
    printf("upperlines eh %d\n", upperLines);
    printf("upperpoints eh %d\n",upperPoints);

    // juntar final do positivo com final do negativo
    gmshModelGeoAddLine(upperPoints, lastPoint, upperLines + 1, &ierr);
    printf("juntando ponto %d de cima com %d de baixo com a linha %d\n", upperPoints, lastPoint,upperLines+1);


    // criando as linhas de baixo going backwards
    int counter = 0;
   
    for (k = lastPoint; k > upperPoints+1; k--) {
        gmshModelGeoAddLine(k, k - 1, upperLines + 1 +1+ counter, &ierr);
        printf("linha %d conecta pontos %d e %d\n", upperLines + 1+1 + counter, k, k - 1);
        counter++;
    }

    // conectando primeiro ponto de baixo com o primeiro de cima

    gmshModelGeoAddLine(1, upperPoints + 1, upperLines + 1 + counter + 1, &ierr);

    printf("juntando ponto %d de cima com %d de baixo na linha %d\n", 1, upperPoints + 1,upperLines+1+counter+1);


    int totalPoints = lastPoint;

    // curve loop
    int cl1[totalPoints];

    for (size_t i = 0; i < upperLines + 2 + counter; i++) {
        cl1[i] = i + 1;

        printf("cl1[%d] eh %d\n", i, i + 1);
    }

    gmshModelGeoAddCurveLoop(cl1, upperLines + 2+counter, 1, 1, &ierr);

    // surface plane
    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);
    gmshModelMeshGenerate(2, &ierr);
    gmshWrite("naca.msh", &ierr);
    gmshFltkRun(&ierr);
    gmshFinalize(&ierr);
}