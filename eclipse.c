#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void extrair_floats(char* linha) {
    float valores[6];
    char* ptr = linha;

    for (int i = 0; i < 6; i++) {
        valores[i] = strtof(ptr, &ptr);
    }

    for (int i = 0; i < 6; i++) {
        printf("Valor %d: %f\n", i + 1, valores[i]);
    }
}

void extrair_e_imprimir_floats(char* linha, int* npoint, double lc, int ierr) {
    double valor1, valor2, valor3;
    char* ptr = linha;

    for (int i = 0; i < 2; i++) {
        // Extrai três floats por vez
        valor1 = strtof(ptr, &ptr);
        valor2 = strtof(ptr, &ptr);
        valor3 = strtof(ptr, &ptr);

        (*npoint)++;
        gmshModelGeoAddPoint(valor1, valor2, valor3, lc, *npoint, &ierr);
        printf("npoint eh %d\n",*npoint);

        // Imprime os valores extraídos
        printf("Valores: %f %f %f\n", valor1, valor2, valor3);
    }
}

int main(int argc, char** argv) {
    int ierr;

    gmshInitialize(argc, argv, 1, 0, &ierr);
    gmshModelAdd("model", &ierr);

    const double lc = 0.01;

    FILE* arq = fopen("data.DATA", "r");
    if (!arq) {
        printf("Erro ao abrir programa");
        exit(1);
    }

    int nx, ny;
    fscanf(arq, "%d %d", &nx, &ny);
    printf("elemento tem %d X e  %d Y", nx, ny);
    fscanf(arq, "*%c");

    char buffer[BUFFER_SIZE];
    char linha[70];
    char* ptr = linha;
    double coord;

    int i = 0, npoint = 1;
    while (fgets(buffer, BUFFER_SIZE, arq) != NULL) {
        extrair_e_imprimir_floats(buffer, &npoint, lc, ierr);
        printf("\n");
    }
    /* for (size_t i = 0; i <= 2; i++) {
        for (size_t j = 0; j <= 1; j++) {\

            fgets(linha, 70, arq);
            for (int i = 0; i < 6; i++) {
                float px= strtof(ptr, &ptr);
                float py= strtof(ptr, &ptr);
                float pz= strtof(ptr, &ptr);

                printf("valores lidos: %.4f || %.4f || %.4f \n",px,py,pz);
            }
        }
    } */

    fclose(arq);
    gmshModelGeoSynchronize(&ierr);
    gmshModelMeshGenerate(2, &ierr);
    gmshWrite("eclipse.msh", &ierr);
    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
