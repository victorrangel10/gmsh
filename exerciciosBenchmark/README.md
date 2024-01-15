<div align="center">
  <h1 align="center">Benchmarks</h1>
  <p align="center"></p>
</div>





## Exercício 1
 Codigo "ex1.c"
 Dados 5 parametros do tipo double, o programa abre um modelo em forma de quadrado com a malha mais refinada nos vertices.
 
 ### Os 5 parâmetros são: 
 
 -mesh size (o tamanho da malha no elementos de contorno)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -tamanho da mesh nos vertices<br/>
 
 
## Exercício 2
 Codigo "ex2.c"
 Dados 5 parametros do tipo double, o programa abre um modelo em forma de quadrado com a malha mais refinada no lado direito.
 
 ### Os 5 parâmetros são: 
 
 -mesh size (o tamanho da malha no elementos de contorno)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -tamanho da mesh no lado<br/>
 
## Exercício 3
 Codigo "ex3.c"
 Dados 4 parametros do tipo double e a orientacao desejada, o programa abre um modelo em forma de quadrado com uma malha estruturada de acordo com a orientacao. 
 
 ### Os 5 parâmetros são: 
 
 -mesh size (o tamanho da malha no elementos de contorno)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -orientacao, que pode ser: "Left", "Right", "AlternateLeft", "AlternateRight"<br/>
 
 ## Exercício 4
 Codigo "ex4-2.c"
 Dados 11 parametros do tipo double, o programa abre um modelo em forma de quadrado com um circulo vazio e a malha mais refinada nos arredores do circulo. 
 
 ### Os 10 parâmetros são: 
 
 -mesh size (o tamanho da malha no elementos de contorno)<br/>
 -coordenadas x e y iniciais do quadrado (relativos a aresta inferior esquerda)<br/>
 -tamanho do lado do quadrado<br/>
 -raio do ciculo<br/>
 -coordenadas do centro do circulo<br/>
 -o numero de pontos a serem computados dentro do círculo a fim de gerar a refinacao da malha: quanto mais pontos, mais refinada sera a malha<br/>
 
 -mesh size mínimo (o menor tamanho de malha nos elementos ao redor do orifício)<br/>
 -mesh size maximo (o maior tamanho de malha nos elementos mais distantes do orifício)<br/>
 -distancia minima  - para distâncias ( ponto - circulo)  menores que esta, o mesh size minímo será aplicado<br/>
 -distancia maxima  - para distâncias ( ponto - circulo)  maiores que esta, o mesh size máximo será aplicado<br/>
 
