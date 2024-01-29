#include <stdio.h>

#include <gmshc.h>
#include <stdlib.h>


int main(int argc, char** argv) {


    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);

    double lc;

    printf("Select mesh size outside from the points\n");

    scanf("%lf",&lc);


    printf("Select square inital coordinates(x,y) and side size\n");

    double initial_x,initial_y,size;

    if(scanf("%lf %lf %lf",&initial_x,&initial_y,&size)!=3){
        exit(1);
    }
 
    printf("Select mesh size on points\n");
    double new_size;
    scanf("%lf",&new_size);

    
    gmshModelAdd("t1", &ierr);

    gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y+size, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y+size, 0, lc, 4, &ierr);

   // gmshModelGeoAddLine(1, 4, 1, &ierr);
   // gmshModelGeoAddLine(4, 3, 2, &ierr);
    //gmshModelGeoAddLine(3, 2, 3, &ierr);
    //gmshModelGeoAddLine(2, 1, 4, &ierr);

    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    gmshModelMeshFieldAdd("Constant", 1, &ierr); // cria campo para adicionar os 4 pontos

    const double pl1[] = {4, 1,2, 3};

    gmshModelMeshFieldSetNumbers(1, "PointsList", pl1, 4, &ierr); // diz a lista de pontos que estarao no campo

    gmshModelMeshFieldSetNumber(1, "VIn", new_size, &ierr); // diz o tamanho do meshsize para os pontos

    gmshModelMeshFieldSetAsBackgroundMesh(1, &ierr); // seta o field criado como background mesh

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("exerciciosBenchmark/QuadradoRefinadoNasPontas/refinadoNasPontas.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
