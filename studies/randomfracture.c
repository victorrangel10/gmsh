#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

int func() {
    double min, max;

    // Semente para a função rand()
    srand(time(NULL));

    printf("Digite o valor mínimo: ");
    scanf("%lf", &min);

    printf("Digite o valor máximo: ");
    scanf("%lf", &max);

    if (min >= max) {
        printf("O valor mínimo deve ser menor que o valor máximo.\n");
        return 1;
    }

    double random_num = random_double(min, max);
    printf("Número aleatório: %lf\n", random_num);

    srand(time(NULL));
    random_num = random_double(min, max);
    printf("Número 2 aleatório: %lf\n", random_num);
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

    double x2, x1, y2, y1;

    srand(time(NULL));

    x1 = random_double(initial_x + 0.2, width / 2);  // de 0.2 ate a metade da largura

    x2 = random_double(x1, width - 0.2);  // pode ir do primeiro ponto ate o final do retangulo

    y1 = random_double(initial_y + 0.2, height / 2);  // de 0.2 ate a metade da altura

    y2 = random_double(y1, height);

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);

    gmshModelGeoAddPoint(x1, y1, 0, lc, 5, &ierr);
    gmshModelGeoAddPoint(x2, y2, 0, lc, 6, &ierr);

    
    gmshModelGeoAddLine(5, 6, 5, &ierr);

    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 6, 0, &ierr);

    const int s1[] = {6};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    int fracture[] = {5};
    gmshModelMeshEmbed(1, fracture, 1, 2, 1, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("exerciciosBenchmark/studies/randomfracture.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);

    return 0;
}
