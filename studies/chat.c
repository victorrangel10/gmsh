#include <stdio.h>
#include <stdlib.h>
#include <gmshc.h>

int main(int argc, char **argv) {
    int ierr;

    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("partition_example", &ierr);

    // Adicionando um retângulo à malha
    gmshModelOccAddRectangle(0, 0, 0, 1, 1, 1, 0, &ierr);

    // Gerando a malha
    gmshModelMeshGenerate(2, &ierr);

    // Obtendo todas as entidades do modelo
    int *allEntities;
    size_t numEntities;
    gmshModelGetEntities(&allEntities, &numEntities, -1, &ierr);

    // Definindo elementos e partições para os elementos - dividindo a malha em 3 partições
    size_t numElements = numEntities;
    size_t numPartitions = 3;
    int *elementTags = (int *)malloc(sizeof(int) * numElements);
    int *partitions = (int *)malloc(sizeof(int) * numElements);

    for (size_t i = 0; i < numElements; ++i) {
        elementTags[i] = allEntities[i];
        partitions[i] = i % numPartitions;  // Atribuindo partições
    }

    // Realizando o particionamento da malha
    gmshModelMeshPartition(numPartitions, elementTags, numElements, partitions, numElements, &ierr);

    // Salvando a malha particionada
    gmshWrite("partitioned_mesh.msh", &ierr);
 gmshFltkRun(&ierr);
    gmshFinalize(&ierr);

    free(allEntities);
    free(elementTags);
    free(partitions);

    return 0;
}