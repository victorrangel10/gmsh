#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

void extrair_e_imprimir_floats(char* linha, int* npoint, double lc, int ierr) {
    double valor1, valor2, valor3;
    char* ptr = linha;

    for (int i = 0; i < 2; i++) {
        // Extrai três floats por vez
        valor1 = strtof(ptr, &ptr);
        valor2 = strtof(ptr, &ptr);
        valor3 = strtof(ptr, &ptr);

        // Imprime os valores extraídos
        printf("Valores: %f %f %f\n", valor1+0.5, valor2+0.5, valor3+0.5);
          (*npoint)++;
        gmshModelGeoAddPoint(valor1, valor2, valor3, lc, *npoint, &ierr);
        printf("npoint eh %d\n",*npoint);
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
    
    fclose(arq);
    gmshModelGeoSynchronize(&ierr); 
    gmshModelMeshGenerate(2, &ierr);
    gmshWrite("eclipse.msh", &ierr);
    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
