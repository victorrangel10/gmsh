## Quadrado Estruturado Com Semicirculo
 Codigo "quadradoComSemicirculo.c"
 Dados 5parametros do tipo double e a orientacao desejada, o programa abre um modelo em forma de quadrado com uma malha estruturada de acordo com a orientacao ao lado de um
 semicirculo desestruturado e gera um arquivo ".msh"

 Para compilar o programa a partir do diretório "gmsh", basta executar o seguinte comando: "gcc -o exerciciosBenchmark/QuadradoComSemicirculo/quadradoComSemicirculo -Iinclude exerciciosBenchmark/QuadradoComSemicirculo/ex5-3.c -Llib -lgmsh
"

 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)
 -tamanho do lado do quadrado
 -orientacao desejada, que pode ser: "Left", "Right", "AlternateLeft", "AlternateRight"
 
#### Exemplo de execução de código:

![image](https://github.com/victorrangel10/gmsh/assets/130004595/0eae17ee-de49-49f7-8287-c08ac17c256f)

![image](https://github.com/victorrangel10/gmsh/assets/130004595/d5d4982b-085c-445c-a4d6-0b9b26f7ffca)



