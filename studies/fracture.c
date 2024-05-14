#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);
    double lc = 0.1;
    double initial_x = 0, initial_y = 0, height = 2, width = 4;

    gmshModelAdd("t1", &ierr);

    gmshModelOccAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelOccAddPoint(initial_x + width, initial_y, 0, lc, 2, &ierr);
    gmshModelOccAddPoint(initial_x + width, initial_y + height, 0, lc, 3, &ierr);
    gmshModelOccAddPoint(initial_x, initial_y + height, 0, lc, 4, &ierr);
 
    gmshModelOccAddPoint(1.5, 0.5, 0, lc, 5, &ierr);
    gmshModelOccAddPoint(3, 1.5, 0, lc, 6, &ierr);

    gmshModelOccAddPoint(2, 1.5, 0, lc, 7, &ierr);
    gmshModelOccAddPoint(3, 0.5, 0, lc, 8, &ierr);

    gmshModelOccAddLine(1, 2, 1, &ierr);
    gmshModelOccAddLine(3, 2, 2, &ierr);
    gmshModelOccAddLine(3, 4, 3, &ierr);
    gmshModelOccAddLine(4, 1, 4, &ierr);

    gmshModelOccAddLine(5, 6, 5, &ierr);  // linha 5
    gmshModelOccAddLine(7, 8, 6, &ierr);  // linha 6

    const int cl1[] = {4, 1, -2, 3};
    gmshModelOccAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 6, &ierr);

    const int s1[] = {6};
    gmshModelOccAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelOccSynchronize(&ierr);

    int aaa[] = {5};
    gmshModelMeshEmbed(1, aaa, 1, 2, 1, &ierr);

    int ObjectDimTags[] = {1, 5};
    int ToolDimTags[] = {1, 6};

    int *outDimTags;
    size_t outDimTags_n;



    gmshModelOccFragment(ObjectDimTags, 2, ToolDimTags, 2, &outDimTags ,&outDimTags_n, NULL, NULL, NULL, 10,0, 0, &ierr);

    printf("outdimtags n eh %d\n", outDimTags_n);
    
    for (size_t i = 0; i < outDimTags_n; i++) {
        double *coord, *parametricCoord;
        size_t coord_n, parametricCoord_n;
        int dim, tag;
        
        gmshModelMeshGetNode(outDimTags[i], &coord, &coord_n, NULL, NULL, &dim, &tag, &ierr);

       
        // Imprimir as coordenadas do ponto de interseção
        printf("Coordenadas do ponto de interseção %zu: (%f, %f, %f)\n", i + 1, coord[0], coord[1], coord[2]);
        
    }
    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("exerciciosBenchmark/studies/fracture.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);

    return 0;
}
