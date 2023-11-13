# Quadrado com Buraco

 Codigo "quadradoComBuraco.c"
 
 Dados 11 parametros do tipo double, o programa abre um modelo em forma de quadrado com um circulo vazio e a malha mais refinada nos arredores do circulo. 
 
 Para compilar o arquivo, basta executar o seguinte comando a partir do diretório "gmsh":
 "gcc -o exerciciosBenchmark/QuadradoComBuraco/quadradocomburaco -Iinclude exerciciosBenchmark/QuadradoComBuraco/quadradoComBuraco.c -Llib -lgmsh"
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
 
 Exemplo de execução do código e malha gerada:
![image](https://github.com/victorrangel10/gmsh/assets/130004595/357f71db-f364-4bec-ad51-eaa85db9aedb)

![image](https://github.com/victorrangel10/gmsh/assets/130004595/c9ee55f4-19fd-49bf-a255-9ea4cf5621db)

