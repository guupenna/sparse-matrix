# sparse_matrix
Trabalho 1 da disciplina Estrutura de Dados - 2023/1

# main1:

tem as funções de criar duas matrizes e salvá-las em binário para serem utilizadas no programa main2. A main1 recebe dois parâmetros, sendo o primeiro o nome da primeira matriz e o segundo o nome da segunda matriz.

código execução:
./main1 <nome_matriz1> <nome_matriz2>

(Possível encaminhar testes da pasta /input)

nesse programa, a saída são as duas matrizes impressas de forma esparsa e densa


# main2:

tem as funções de operações e recebe como parâmetro alem do nome de duas matrizes salvas em binario anteriormente na main1 que serão buscadas na pasta binary, e o nome da matriz que sera usada como kernel na funcao de convolucao, a matriz de saida onde pode ser gerado o arquivo binario de saida de alguma operação

código execução:
./main2 <nome_matriz1> <nome_matriz2> <nome_kernel> <nome_matriz_saida>

nesse programa, existe uma interface para execução das demais operações (operações feitas com apenas uma matriz são sempre realizadas com a matriz1, ou seja, a primeira a ser passada como parâmetro na main2)
