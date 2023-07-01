##Trabalho final:
1. Ler mais de um OBJ OK
>>Lendo um objeto com textura, next, ler dois objetos, ver as 3 suzanes
a. já triangularizado, com normais e coordenadas de texturas
b. cada objeto ou grupo1 (submesh) possui seu índice de textura e suas propriedades do material (ka, ks e kd) - que devem ser usados no shader de iluminação

2. Ter pelo menos uma fonte de luz, iluminação de Phong - feito, mas ainda não estpa funcionando
a. Acrescentar os coeficientes ka, ks e kd do arquivo de materiais (.mtl)
b. Preferencialmente, deixar todos os coeficientes de iluminação 
parametrizáveis (intensidade das fontes de luz, coeficiente da especular)

3. Controle de câmera por teclado e/ou mouse, provendo navegabilidade para a cena.

4. Seleção dos objetos via teclado e/ou mouse, permitindo a aplicação de operações 
geométricas (rotação, translação e escala uniforme) - NÃO FAÇO IDEIA DE COMO FAZER!

5. A especificação dos objetos passa a ser por meio do arquivo de configuração de cena, 
contendo:
a. Definições sobre os .objs a serem instanciados na cena
i. nome do arquivo
ii. transformações iniciais (rot, trans, escala)
iii. Em alguns objetos, alguma predefinição de animação (trajetória com 
curvas paramétricas) - OUT
b. Informação da(s) fonte(s) de luz
c. Posição e orientação inicial da câmera, assim como a definição do frustrum.