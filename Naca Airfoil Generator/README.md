# Gerador de malha para Aerofólio NACA de 4 dígitos
Código construído com o propósito de gerar malhas .msh de um Airfoil de 4 dígitos quaisquer, dados os seus parâmetros de entrada.

#### Utilização e Funcionamento
O único parâmetro do programa é o número do airfoil, no modelo "xxxx", onde: </br>

- O primeiro dígito descreve a curvatura máxima como porcentagem da corda média.</br>
- O segundo dígito indica a distância da curvatura máxima a partir da borda de ataque do aerofólio, expressa em décimos da corda. </br>
- Os dois últimos dígitos indicam a espessura máxima do aerofólio em porcentagem da corda.

Por exemplo, um aerofólio NACA 2412 tem uma curvatura máxima de 2%, localizada a 40% (0.4 cordas) da borda de ataque, com uma espessura máxima de 12% da corda. </br>

O aerofólio NACA 0012 é simétrico, o 00 indica que não possui curvatura. O 12 indica que o aerofólio tem uma proporção de 12% entre espessura e comprimento da corda: é 12% mais grosso que longo. </br>

### Saída
O programa gera um arquivo .msh (versão 4.1) contendo os elementos do aerófolio desejado, para que seja usado posteriormente em projetos.

![image](https://github.com/victorrangel10/gmsh/assets/130004595/05113b8c-5dad-442a-9069-8a328eeeb975)</br>
Exemplo de NACA 0012.


