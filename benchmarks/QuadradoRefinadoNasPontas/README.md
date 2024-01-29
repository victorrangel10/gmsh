## Quadrado Refinado nas Pontas
Codigo "square.c"

Dados 5 parametros do tipo double, o programa abre um modelo em forma de quadrado com a malha mais refinada nos vertices e gera um arquivo ".msh"

### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)
 -tamanho do lado do quadrado
 -tamanho da mesh nos vertices
 
Para compilar o arquivo, basta executar o seguinte comando a partir do diretório "gmsh": "gcc -o exerciciosBenchmark/QuadradoRefinadoNasPontas/refinadoNasPontas -Iinclude exerciciosBenchmark/QuadradoRefinadoNasPontas/square.c -Llib -lgmsh"


Exemplo de execução do código e malha gerada:
![Imagem do resultado de saida do terminal](https://github.com/victorrangel10/gmsh/assets/130004595/1ed8fc8c-fb34-42ce-bc0c-9354b3c069fb)

![Imagem da malha gerada](https://github.com/victorrangel10/gmsh/assets/130004595/85980817-80a2-4a5f-8dc8-a9e940f15af3)
