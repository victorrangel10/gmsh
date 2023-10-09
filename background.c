#include <gmshc.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshMerge("t7_bgmesh.pos", &ierr);

    gmshModelAdd("t7", &ierr);

    double lc = 0.01;

    gmshModelGeoAddPoint(0, 0, 0, lc, 1, &ierr);
    gmshModelGeoAddPoint(.1, 0, 0, lc, 2, &ierr);
    gmshModelGeoAddPoint(.1, .3, 0, lc, 3, &ierr);
    gmshModelGeoAddPoint(0, .3, 0, lc, 4, &ierr);
    gmshModelGeoAddLine(1, 2, 1, &ierr);
    gmshModelGeoAddLine(3, 2, 2, &ierr);
    gmshModelGeoAddLine(3, 4, 3, &ierr);
    gmshModelGeoAddLine(4, 1, 4, &ierr);
    const int cl1[] = {4,1 ,-2 ,3};
    gmshModelGeoAddCurveLoop(cl1, sizeof(cl1) / sizeof(cl1[0]), 1, 0, &ierr);
    const int s1[] = {1};
    gmshModelGeoAddPlaneSurface(s1, sizeof(s1) / sizeof(s1[0]), 1, &ierr);
    gmshModelGeoSynchronize(&ierr);
    
    int bg_field = gmshModelMeshFieldAdd("PostView", 1, &ierr);

    gmshModelMeshFieldSetNumber(1, "ViewIndex", 0, &ierr);

    gmshModelMeshFieldSetAsBackgroundMesh(1, &ierr);

    gmshOptionSetNumber("Mesh.MeshSizeExtendFromBoundary", 0,&ierr);

    gmshOptionSetNumber("Mesh.MeshSizeFromPoints", 0,&ierr);

    gmshOptionSetNumber("Mesh.MeshSizeFromCurvature", 0, &ierr);

    gmshModelMeshGenerate(2, &ierr);

    gmshWrite("back.msh", &ierr);

    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);
    return 0;
}