#include <stdio.h>
#include <gmshc.h>

int main(int argc, char **argv){
    int ierr;

    gmshInitialize(argc,argv,1,0,&ierr);

    gmshModelAdd("fields", &ierr);

     const double lc = 0.1;

    gmshModelGeoAddPoint(.2, 0, 0, lc, 1, &ierr);

    
    gmshModelGeoAddPoint(-.2, 0, 0, lc/5, 2, &ierr);


    gmshModelGeoAddPoint(.2, .2, 0, lc, 3, &ierr);
    
    gmshModelGeoAddPoint(-.2, .2, 0, lc, 4, &ierr);


    gmshModelGeoAddLine(1,2,1,&ierr);
    gmshModelGeoAddLine(2,4,2,&ierr);
    gmshModelGeoAddLine(4,3,3,&ierr);
    gmshModelGeoAddLine(3,1,4,&ierr);
    const int cl1[] = {1,2, 3, 4};

    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);

    const int s1[] = {1};

    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);

    gmshModelGeoSynchronize(&ierr);

    //cria um field do tipo distancia do ponto 5 a curva 2 com 100 pontos equidistantes
    gmshModelMeshFieldAdd("Distance",1,&ierr);

    double pl1[]={5};
    gmshModelMeshFieldSetNumbers(1,"PointsList",pl1,1,&ierr);

    double cl2[]={2};
    gmshModelMeshFieldSetNumbers(1,"CurvesList",cl2,1,&ierr);

    gmshModelMeshFieldSetNumber(1,"Sampling",100,&ierr);

    //
    gmshModelMeshFieldAdd("Threshold",2,&ierr);

    gmshModelMeshFieldSetNumber(2,"InField",1,&ierr);

    gmshModelMeshFieldSetNumber(2,"SizeMin",lc/30,&ierr);

    gmshModelMeshFieldSetNumber(2,"SizeMax",lc,&ierr);

    gmshModelMeshFieldSetNumber(2,"DistMin",0.15,&ierr);

    gmshModelMeshFieldSetNumber(2,"DistMax",0.5,&ierr);

    // junta as duas

    gmshModelMeshFieldAdd("Min",3,&ierr);

    double fl[]={1,2};

    gmshModelMeshFieldSetNumbers(3,"FieldsList",fl,2,&ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(3,&ierr);

    gmshOptionSetNumber("Mesh.MeshSizeExtendFromBoundary", 0,&ierr);

    gmshOptionSetNumber("Mesh.MeshSizeFromPoints", 0,&ierr);

    gmshOptionSetNumber("Mesh.MeshSizeFromCurvature", 0, &ierr);

    gmshOptionSetNumber("Mesh.Algorithm", 5, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("fields.msh",&ierr);
    gmshFltkRun(&ierr);
    gmshFinalize(&ierr);
    return 0;

}