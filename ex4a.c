#include <stdio.h>

#include "gmshc.h"

int main(int argc, char** argv) {

     const double lc = 1e-2/2;

    int ierr;
    gmshInitialize(argc, argv, 1, 0, &ierr);
    gmshModelAdd("t1", &ierr);

    gmshModelOccAddRectangle(0.1,0.1,0,.1,.1,1,0,&ierr);

    gmshModelOccAddCircle(0.15,0.14,0,0.03,0,0,2*3.14,0,0,0,0,&ierr);
    
    gmshModelOccSynchronize(&ierr);
    gmshModelMeshGenerate(2, &ierr);
    gmshWrite("ex4a.msh", &ierr);
    gmshFltkRun(&ierr);

    gmshFinalize(&ierr);

}