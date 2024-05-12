#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

int main() {
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
    return 0;
}