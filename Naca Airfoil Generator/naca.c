#include <gmshc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double GetMeanLinePoint(float m, float p, float x) {
    double y;

    if (x <= p) {
        y = (m / p * p) * ((2 * p * x) - (x * x));
    } else {
        y = ((m / (1-p)*(1-p)) * ((1 - (2 * p)) + (2 * p * x) - (x * x)));
    }

    return y;
}

int main(int argc, char** argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("naca", &ierr);

    const double lc = 0.015;
    double x = 0;
    int i = 0;

    float jump = 0.02;

    printf("Insert the four NACA digits: \n");
    int m, p, t;

    scanf("%1d%1d%d", &m, &p, &t);

    double max_camber = (double) m / 100;
    printf("max camber is %f\n",max_camber);

    double max_camber_location =(double) p / 10;
    printf("max location is %f\n",max_camber_location);

    double thickness = (double) t / 100;
    printf("max thickness is %f\n",thickness);

    int lastPoint;
    int k;
    int c = 2000; //tag dos pontos da linha media
    int simetrical =1;

    if (max_camber || max_camber_location) {
        simetrical=0;
        // gerando a linha de curvatura media
        for (double x = 0; x < max_camber_location; x += jump) {
            c++;
            double y = GetMeanLinePoint(max_camber,max_camber_location,x);
            printf("criando ponto (mean line -1) %d, x vale %f e y %f\n", c, x, y);
            gmshModelGeoAddPoint(x, y, 0, lc, c, &ierr);
        }
        for (double x = max_camber_location; x <= 1.01; x+=jump) {
            c++;
            double y = GetMeanLinePoint(max_camber,max_camber_location,x);
            printf("criando ponto (mean line -2) %d, x vale %f e y %f\n", c, x, y);
            gmshModelGeoAddPoint(x, y, 0, lc, c, &ierr);
        }
    }

    // criando os pontos de cima
    i = 0;
    float bending;
    for (x = 0; x < 1.01; x += jump) {
        i++;
        if (simetrical)
        {
            bending = 0;
        }else{
            bending = GetMeanLinePoint(max_camber,max_camber_location,x);
        }
        
        // definindo funcao
        double y = 5 * thickness * ((0.2969 * sqrt(x)) - (0.1260 * x) - (0.3516 * x * x) + (0.2843 * x * x * x) - (0.1015 * pow(x, 4)))+bending;
        printf("criando ponto %d, x vale %f e y %f\n", i, x, y);
        gmshModelGeoAddPoint(x, y, 0, lc, i, &ierr);
    }

    int upperPoints = i;  // obtem o numero de pontos que ja foram

    // criando os pontos de baixo
    i = 0;
    int totalPoints = 0;

    for (x = 1; x > 0.00; x -= jump) {
        i++;
        if (simetrical)
        {
            bending =0;
        }else{
            bending = GetMeanLinePoint(max_camber,max_camber_location,x);
        }
        double y = -1 * 5 * thickness * ((0.2969 * sqrt(x)) - (0.1260 * x) - (0.3516 * x * x) + (0.2843 * x * x * x) - (0.1015 * pow(x, 4)))+bending;
        printf("criando ponto %d, x vale %f e y %f\n", i + upperPoints, x, y);
        gmshModelGeoAddPoint(x, y, 0, lc, i + upperPoints, &ierr);
    }

    lastPoint = i + upperPoints;

    // printf("total de pontos eh %d\n",lastPoint);

    // criando as linhas
    for (k = 1; k < lastPoint; k++) {
        gmshModelGeoAddLine(k, k + 1, k, &ierr);
        printf("linha %d conecta pontos %d e %d\n", k, k, k + 1);
    }

    // juntando ponto final com ponto inicial
    printf("juntando ponto final %d com ponto inicial %d com a linha %d\n", lastPoint, 1, k);
    gmshModelGeoAddLine(lastPoint, 1, k, &ierr);

    // curve loop
    int cl1[lastPoint];
    for (size_t i = 0; i < lastPoint; i++) {
        cl1[i] = i + 1;

        printf("cl1[%d] eh %d\n", i, i + 1);
    }
    gmshModelGeoAddCurveLoop(cl1, lastPoint, 1, 0, &ierr);

    gmshModelAddPhysicalGroup(1, cl1, lastPoint, 1, "NACA", &ierr);

    // criando circulo
    const double x_center = 0, y_center = 0, raio = 2;
    gmshModelGeoAddPoint(x_center, y_center, 0, lc * 10, 1001, &ierr);         // centro
    gmshModelGeoAddPoint(x_center, y_center + raio, 0, lc * 10, 1002, &ierr);  // topo
    gmshModelGeoAddPoint(x_center, y_center - raio, 0, lc * 10, 1003, &ierr);  // parte mais baixa
    gmshModelGeoAddCircleArc(1002, 1001, 1003, 1100, 0, 0, 0, &ierr);          // adicionando circulo
    gmshModelGeoAddCircleArc(1003, 1001, 1002, 1110, 0, 0, 0, &ierr);          // adicionando circulo

    const int cl2[] = {1100, 1110};

    gmshModelGeoAddCurveLoop(cl2, sizeof(cl2) / sizeof(cl2[0]), 2, 0, &ierr);

    // surface plane
    const int s1[] = {2, 1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);
    gmshModelMeshGenerate(2, &ierr);
    gmshWrite("naca.msh", &ierr);
    gmshFltkRun(&ierr);
    gmshFinalize(&ierr);
}