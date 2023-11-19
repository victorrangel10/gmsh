#include <gmshc.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int ierr;

    gmshInitialize(argc, argv, 1, 0, &ierr);

    gmshModelAdd("square", &ierr);

    gmshModelOccAddRectangle(0, 0, 0, 1, 1, 1, 0, &ierr);

    gmshModelOccAddRectangle(.5, .5, 0, .5, .5, 2, 0, &ierr);

    int objectDimTags[] = {2, 1};  // Definindo a superfície 1 como objeto
    int toolDimTags[] = {2, 2};    // Definindo a superfície 2 como ferramenta

    int *outDimTags; // array de inteiros que representará as tags das entidades retornadas pela função.
    size_t outDimTags_n;
    int **outDimTagsMap;
    size_t *outDimTagsMap_n;
    size_t outDimTagsMap_nn;

    int tag = -1;          // Neste exemplo, não estamos definindo uma tag específica
    int removeObject = 1;  //  remover a superfície objeto após a operação
    int removeTool = 1;    //  remover a superfície ferramenta após a operação


    gmshModelOccFragment(objectDimTags, sizeof(objectDimTags) / sizeof(objectDimTags[0]),
                         toolDimTags, sizeof(toolDimTags) / sizeof(toolDimTags[0]),
                         &outDimTags, &outDimTags_n,
                         &outDimTagsMap, &outDimTagsMap_n, &outDimTagsMap_nn,
                         tag, removeObject, removeTool, &ierr);

    // Sincroniza as alterações no modelo
    gmshModelOccSynchronize(&ierr);

    // Obtém todas as entidades do modelo
    int *tmp;
    size_t tmp_n;
    gmshModelGetEntities(&tmp, &tmp_n, 0, &ierr);

    // Define o tamanho da malha para as entidades presentes em tmp como 0.05
    double size = 0.05;
    gmshModelMeshSetSize(tmp, tmp_n, size, &ierr);

    // Criando grupos físicos para os quadrados resultantes e gerando a malha
    int physLeft = gmshModelAddPhysicalGroup(2, &outDimTags[0], outDimTags_n, 100, "Left", &ierr);
    int physRight = gmshModelAddPhysicalGroup(2, &outDimTags[1], outDimTags_n, 200, "Right", &ierr);

    gmshModelMeshGenerate(2, &ierr);

    // Define constantes para particionamento da malha
    gmshOptionSetNumber("Mesh.PartitionCreateTopology", 1, &ierr);
    gmshOptionSetNumber("Mesh.PartitionCreateGhostCells", 1, &ierr);
    gmshOptionSetNumber("Mesh.PartitionCreatePhysicals", 0, &ierr);
    gmshOptionSetNumber("Mesh.PartitionOldStyleMsh2", 0, &ierr);
    gmshOptionSetNumber("Mesh.PartitionSplitMeshFiles", 0, &ierr);

    gmshWrite("partition.msh", &ierr);
    int partitioner = 0;  // 0 para Metis, 1 para SimplePartition
    int N = 3;            // Número de partições

    if (partitioner == 0) {
        // Usa Metis para criar N partições
        gmshModelMeshPartition(3, tmp, tmp_n, NULL, NULL, &ierr);
    } else {
        // Usa o plugin SimplePartition para criar partições
        gmshPluginSetNumber("SimplePartition", "NumSlicesX", 3, &ierr);
        gmshPluginSetNumber("SimplePartition", "NumSlicesY", 1, &ierr);
        gmshPluginSetNumber("SimplePartition", "NumSlicesZ", 1, &ierr);
       
        gmshPluginRun("SimplePartition", &ierr);
    }
    

    gmshFltkRun(&ierr);
    gmshFinalize(&ierr);
    return 0;
}
