<div align="center">
  <h1 align="center">Benchmarks</h1>
  <p align="center"></p>
</div>





## Exercício 1
 Codigo "ex1.c"
 Dados 5 parametros do tipo double, o programa abre um modelo em forma de quadrado com a malha mais refinada nos vertices.
 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -tamanho da mesh nos vertices<br/>
 
 
## Exercício 2
 Codigo "ex2.c"
 Dados 5 parametros do tipo double, o programa abre um modelo em forma de quadrado com a malha mais refinada no lado direito.
 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -tamanho da mesh no lado<br/>
 
## Exercício 3
 Codigo "ex3.c"
 Dados 4 parametros do tipo double e a orientacao desejada, o programa abre um modelo em forma de quadrado com uma malha estruturada de acordo com a orientacao. 
 
 ### Os 5 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -orientacao, que pode ser: "Left", "Right", "AlternateLeft", "AlternateRight"<br/>
 
 ## Exercício 4
 Codigo "ex4-2.c"
 Dados 11 parametros do tipo double, o programa abre um modelo em forma de quadrado com um circulo vazio e a malha mais refinada nos arredores do circulo. 
 
 ### Os 10 parametros sao: 
 
 -mesh size (o tamanho geral da mesh dentro do quadrado)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -raio do ciculo<br/>
 -coordenadas do centro do circulo<br/>
 -o numero de pontos a serem computados dentro do cirulo a fim de gerar a refinacao da malha: quanto mais pontos, mais refinada sera a malha<br/>
 -mesh size mínimo (mais perto dos pontos computados acima)<br/>
 -mesh size maximo (mais longe dos pontos computados acima)<br/>
 -distancia minima dos pontos - abaixo dessa distancia será aplicada o mesh size minimo<br/>
 -distancia maxima dos pontos - acima dessa distancia será aplicada o mesh size maximo<br/>
 
