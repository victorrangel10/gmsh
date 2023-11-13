#include <stdio.h>

#include <gmshc.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    

    int ierr;


    double lc;

    printf("Select mesh size outside from the line\n");

    scanf("%lf",&lc);


    printf("Select square inital coordinates(x,y) and side size\n");

    double initial_x,initial_y,size;

    if(scanf("%lf %lf %lf",&initial_x,&initial_y,&size)!=3){
        exit(1);
    }
 
    printf("Select mesh size on the line\n");
    double new_size;
    scanf("%lf",&new_size);




    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("t1", &ierr);

     gmshModelGeoAddPoint(initial_x, initial_y, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(initial_x + size, initial_y+size, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(initial_x, initial_y+size, 0, lc, 4, &ierr);

    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);


    const int cl1[] = {4, 1, -2, 3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);


    gmshModelMeshFieldAdd("Constant", 1, &ierr); // ria campo para adicionar a reta

    const double pl1[] = {2};

    gmshModelMeshFieldSetNumbers(1, "CurvesList", pl1, 1, &ierr); // bota  a reta como pertecente ao campo

    gmshModelMeshFieldSetNumber(1, "VIn", new_size, &ierr); // diz o tamanho do meshsize para a reta

    gmshModelMeshFieldSetAsBackgroundMesh(1, &ierr); // seta o field criado como background mesh



    //gmshOptionSetNumber("Mesh.MeshSizeExtendFromBoundary", 0, &ierr);

    //gmshOptionSetNumber("Mesh.MeshSizeFromPoints", 0, &ierr);

    //gmshOptionSetNumber("Mesh.MeshSizeFromCurvature", 0, &ierr);

    //gmshOptionSetNumber("Mesh.Algorithm", 5, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("exerciciosBenchmark/QuadradoLadoRefinado/ladoRefinado.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}
