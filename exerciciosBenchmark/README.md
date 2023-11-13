<div align="center">
  <h1 align="center">Benchmarks</h1>
  <p align="center">S</p>
</div>





## Exercício 1
 Codigo "ex1.c"
 Dados 5 parametros do tipo double, o programa abre um modelo em forma de quadrado com a malha mais refinada nos vertices.
 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)
 -tamanho do lado do quadrado
 -tamanho da mesh nos vertices
 
 
## Exercício 2
 Codigo "ex2.c"
 Dados 5 parametros do tipo double, o programa abre um modelo em forma de quadrado com a malha mais refinada no lado direito.
 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)
 -tamanho do lado do quadrado
 -tamanho da mesh no lado
 
## Exercício 3
 Codigo "ex3.c"
 Dados 4 parametros do tipo double e a orientacao desejada, o programa abre um modelo em forma de quadrado com uma malha estruturada de acordo com a orientacao. 
 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)
 -tamanho do lado do quadrado
 -orientacao, que pode ser: "Left", "Right", "AlternateLeft", "AlternateRight"
 
 ## Exercício 4
 Codigo "ex4-2.c"
 Dados 11 parametros do tipo double, o programa abre um modelo em forma de quadrado com um circulo vazio e a malha mais refinada nos arredores do circulo. 
 
 ### Os 10 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)
 -tamanho do lado do quadrado
 -raio do ciculo
 -coordenadas do centro do circulo
 -o numero de pontos a serem computados dentro do cirulo a fim de gerar a refinacao da malha: quanto mais pontos, mais refinada sera a malha
 -mesh size mínimo (mais perto dos pontos computados acima)
 -mesh size maximo (mais longe dos pontos computados acima)
 -distancia minima dos pontos - abaixo dessa distancia será aplicada o mesh size minimo
 -distancia maxima dos pontos - acima dessa distancia será aplicada o mesh size maximo
 
 


