#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 256

typedef struct 
{
    double coord_x, coord_y;
    float permx,permy,poro;
    int id;
}tPoint;


int expand_notation(FILE *arquivo)
{
    int n = 0;
    int count;
    float value;

    while (1)
    {
        int result = fscanf(arquivo, "%d*%f", &count, &value);
        if (result == 2)
        {
            // printf("count eh %d, n eh %.2f\n",count,value);
            n += count;
        }
        else
        {
            result = fscanf(arquivo, "%f", &value);
            if (result == 1)
            {
                n++;
            }
            else if (result == EOF)
            {
                break;
            }
            else
            {
                // Pular qualquer caractere inválido
                fscanf(arquivo, "%*c");
            }
        }
    }

    return n;
}

int ler_perms(FILE *arquivo)
{
    int n = 0;
    int count, value;
    while (1)
    {
        int result = fscanf(arquivo, "%d*%d", &count, &value);
        if (result == 2)
        {
            n += count;
        }
        else
        {
            if (result == 1)
            {
                n++;
            }
            if (result == 0)
            {
                break;
            }
            else if (result == EOF)
            {

                break;
            }
        }
    }
    return n;
}

void ler_zcorn(FILE *arq)
{
    float f1, f2, f3, f4, f5, f6;
    int n = 0;
    while (fscanf(arq, "%f %f %f %f %f %f", &f1, &f2, &f3, &f4, &f5, &f6) == 6)
    {
        n += 6;
    }
    printf(" li %d zcorns\n", n);
}

void convert_float_to_coordinate(char *linha, int *npoint, double lc, int ierr)
{
    double valor1, valor2, valor3;
    char *ptr = linha;

    for (int i = 0; i < 2; i++)
    {
        // Extrai três floats por vez
        valor1 = strtod(ptr, &ptr);
        valor2 = strtod(ptr, &ptr);
        valor3 = strtod(ptr, &ptr);

        // Imprime os valores extraídos
        // printf("Valores lidos: %f %f %f\n", valor1, valor2, valor3);
        
        
        if (i==1) // pega so a parte de cima
        {
            continue;
        }
        (*npoint)++;
        
        if(*npoint<=15) printf("criando ponto %d em:(%.2f,%.2f)\n",*npoint,valor1,valor2);
        gmshModelGeoAddPoint(valor1, valor2, 0, lc, *(npoint), &ierr);
    }
}

int main(int argc, char **argv)
{
    FILE *zcorn = fopen("ZCORN.txt", "r");
    FILE *poros = fopen("porosidades.txt", "r");
    FILE *arq = fopen("data.DATA", "r");
    FILE *permy = fopen("PERMY.txt", "r");
    FILE *permx = fopen("PERMX.txt", "r");
    FILE *permz = fopen("PERMZ.txt", "r");
    char buffer[BUFFER_SIZE];
    char linha[70];
    char *ptr = linha;
    double coord;
    const double lc = 0.1;
    int i = 0, npoint = 0;
    int ierr;


    if (!arq || !zcorn || !poros || !permx || !permy || !permz)
    {
        printf("Erro ao abrir programa");
        exit(1);
    }
    int nx, ny, nz;
    fscanf(arq, "%d %d %d*%c", &nx, &ny, &nz);
    printf("X*Y*Z =%d*%d*%d = %d\n", nx, ny, nz, nx * ny * nz);

    gmshInitialize(argc, argv, 1, 0, &ierr);
    
    gmshModelAdd("model", &ierr);

    fgets(buffer, BUFFER_SIZE, arq);
    while (fgets(buffer, BUFFER_SIZE, arq) != NULL)
    {
        convert_float_to_coordinate(buffer, &npoint, lc, ierr);
    }

    int n = expand_notation(poros);
    printf(" li %d valores porosidades\n", n);

    n = ler_perms(permx);
    printf(" li %d valores permx \n", n);

    n = ler_perms(permy);
    printf(" li %d valores permy \n", n);

    n = ler_perms(permz);
    printf(" li %d valores permz \n", n);

    
    ler_zcorn(zcorn);

    fclose(arq);
    gmshModelGeoSynchronize(&ierr);
    gmshModelMeshGenerate(2, &ierr);
    gmshWrite("eclipse.msh", &ierr);
    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
