## Quadrado com Malha Estruturada
 Codigo "quadradoEstruturado.c"
 Dados 4 parametros do tipo double e a orientacao desejada, o programa abre um modelo em forma de quadrado com uma malha estruturada de acordo com a orientacao e 
 gera um arquivo ".msh"

 Para compilar o programa a partir do diretório "gmsh", basta executar o seguinte comando: "gcc -o exerciciosBenchmark/QuadradoMalhaEstruturada/quadradoEstruturado -Iinclude exerciciosBenchmark/QuadradoMalhaEstruturada/quadradoEstruturado.c -Llib -lgmsh"

 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)
 -tamanho do lado do quadrado
 -orientacao desejada, que pode ser: "Left", "Right", "AlternateLeft", "AlternateRight"
 

### Exemplo de execução de código:
![image](https://github.com/victorrangel10/gmsh/assets/130004595/ee2eb047-fa43-4471-9ada-9da1b284ed61)

![image](https://github.com/victorrangel10/gmsh/assets/130004595/6a769aba-0fd4-484f-90a7-6da02dd17b5a)
