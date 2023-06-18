#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

void printData(data_type data)
{
    printf("%.0f", data);
}

int main(int argc, char *argv[])
{   
    Matriz *matriz1=NULL, *matriz2=NULL,
    *matrizSum=NULL, *matrizScalar=NULL, *matrizDot=NULL, *matrizSwapRow=NULL, *matrizSwapColumn=NULL, *matrizSlice=NULL, *matrizTranspose=NULL, *matrizConvolution=NULL, *kernel=NULL;
    int row, column, scalar, rowSwap1, rowSwap2, columnSwap1, columnSwap2, startRow, startColumn, endRow, endColumn;
    data_type value;

    FILE *binaryMatrizRead, *binaryMatrizRead2, *binaryKernelRead, *binaryMatrizWrite;
    char caminho[300];

    sprintf(caminho, "binary/%s.bin", argv[1]);
    binaryMatrizRead = fopen(caminho, "rb");

    sprintf(caminho, "binary/%s.bin", argv[2]);
    binaryMatrizRead2 = fopen(caminho, "rb");

    sprintf(caminho, "binary/%s.bin", argv[3]);
    binaryKernelRead = fopen(caminho, "rb");

    sprintf(caminho, "binary/%s.bin", argv[4]);
    binaryMatrizWrite = fopen(caminho, "wb");

    if (binaryMatrizRead == NULL)
    {
        exit(printf("ERRO: Não foi possível abrir o arquivo com o caminho %s para leitura\n", argv[1]));
    }

    if (binaryMatrizRead2 == NULL)
    {
        exit(printf("ERRO: Não foi possível abrir o arquivo com o caminho %s para leitura\n", argv[2]));
    }

    if (binaryKernelRead == NULL)
    {
        exit(printf("ERRO: Não foi possível abrir o arquivo com o caminho %s para leitura\n", argv[2]));
    }

    if (binaryMatrizWrite == NULL)
    {
        exit(printf("ERRO: Não foi possível abrir o arquivo com o caminho %s para escrita\n", argv[4]));
    }

    matriz1 = matriz_read_binary(binaryMatrizRead);
    matriz2 = matriz_read_binary(binaryMatrizRead2);

    printf("\nEscolha uma opção:\n\n");
    printf("\n1 - Adicionar valor em uma célula\n2 - Ler valor de uma célula\n3 - Soma de matrizes\n4 - Multiplicação de matriz por escalar\n5 - Multiplicar matrizes ponto a ponto\n6 - Swap de linhas\n7 - Swap de colunas\n8 - Slicing da matriz\n9 - Transposta da matriz\n10 - Convolução da matriz\n0 - Fechar o programa\n");
    printf("\n---------------------------\n\n");
    printf("=> ");

    int option;
    while (scanf("%d", &option))
    {
        int flagExit = 0;

        switch(option)
        {
            case 1:
            printf("Digite a linha da célula a alterar o valor:\n=> ");
            scanf("%d", &row);
            printf("Digite a coluna da célula a alterar o valor:\n=> ");
            scanf("%d", &column);
            printf("Digite o valor que será adicionado:\n=> ");
            scanf("%f", &value);

            matriz_set_value(matriz1, row, column, value);
            printf("\n - Matriz:\n");
            matriz_print(matriz1, printData, DENSE);
            break;

            case 2:
            printf("\nDigite a linha da célula a ser lida:\n=> ");
            scanf("%d", &row);
            printf("\nDigite a coluna da célula a ser lida:\n=> ");
            scanf("%d", &column);

            value = matriz_read_value(matriz1, row, column);
            printf("- Matriz:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("\nValor: ");
            printData(value);
            printf("\n");
            break;
            
            case 3:
            matrizSum = matriz_sum(matriz1, matriz2);

            printf("- Matriz 1:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("- Matriz 2:\n");
            matriz_print(matriz2, printData, DENSE);
            printf("\n- Matriz soma:\n");
            matriz_print(matrizSum, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizSum, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizSum);
            break;

            case 4:
            printf("\nDigite um escalar: ");
            scanf("%d", &scalar);

            matrizScalar = matriz_scalar_mult(matriz1, scalar);
            printf("- Matriz original:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("\n- Matriz produto por escalar:\n");
            matriz_print(matrizScalar, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizScalar, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizScalar);
            break;

            case 5:
            matrizDot = matriz_dot_mult(matriz1, matriz2);
            printf("- Matriz 1:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("- Matriz 2:\n");
            matriz_print(matriz2, printData, DENSE);
            printf("\n- Matriz multiplicação de ponto a ponto:\n");
            matriz_print(matrizDot, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizDot, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizDot);
            break;

            case 6:
            printf("\nDigite os índices das duas linhas a serem trocadas: ");
            scanf("%d %d", &rowSwap1, &rowSwap2);

            matrizSwapRow = matriz_swap_row(matriz1, rowSwap1, rowSwap2);
            printf("- Matriz original:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("- Matriz swap linhas:\n");
            matriz_print(matrizSwapRow, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizSwapRow, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizSwapRow);
            break;

            case 7:
            printf("\nDigite os índices das duas colunas a serem trocadas: ");
            scanf("%d %d", &columnSwap1, &columnSwap2);

            matrizSwapColumn = matriz_swap_column(matriz1, columnSwap1, columnSwap2);
            printf("- Matriz original:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("- Matriz swap colunas:\n");
            matriz_print(matrizSwapColumn, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizSwapColumn, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizSwapColumn);
            break;

            case 8:
            printf("\nDigite o ponto inicial (linha e coluna) do slicing da matriz: ");
            scanf("%d %d", &startRow, &startColumn);
            printf("\nDigite o ponto final (linha e coluna) do slicing da matriz: ");
            scanf("%d %d", &endRow, &endColumn);

            matrizSlice = matriz_slice(matriz1, startRow, startColumn, endRow, endColumn);
            printf("- Matriz original:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("- Matriz slice:\n");
            matriz_print(matrizSlice, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizSlice, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizSlice);
            break;

            case 9:
            matrizTranspose = matriz_transpose(matriz1);
            printf("- Matriz original:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("- Matriz transposta:\n");
            matriz_print(matrizTranspose, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizTranspose, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizTranspose);
            break;

            case 10:
            kernel = matriz_read_binary(binaryKernelRead);
            matrizConvolution = matriz_convolution(matriz1, kernel);
            printf("- Matriz original:\n");
            matriz_print(matriz1, printData, DENSE);
            printf("- Matriz convolucionada:\n");
            matriz_print(matrizConvolution, printData, DENSE);

            printf("Salvar essa matriz em binário?\n0 - não\n1 - sim\n\n=> ");
            scanf("%d", &option);
            if (option) {
                matriz_write_binary(matrizConvolution, binaryMatrizWrite);
                flagExit = 1;
            }
            matriz_destroy(matrizConvolution);
            matriz_destroy(kernel);
            break;

            case 0:
            flagExit = 1;
            break;
        }
        if (flagExit)
        {
            break;
        }
        printf("\nEscolha uma opção:\n\n");
        printf("\n1 - Adicionar valor em uma célula\n2 - Ler valor de uma célula\n3 - Soma de matrizes\n4 - Multiplicação de matriz por escalar\n5 - Multiplicar matrizes ponto a ponto\n6 - Swap de linhas\n7 - Swap de colunas\n8 - Slicing da matriz\n9 - Transposta da matriz\n10 - Convolução da matriz\n0 - Fechar o programa\n");
        printf("\n---------------------------\n\n");
        printf("=> ");
    }

    fclose(binaryMatrizRead);
    fclose(binaryMatrizRead2);
    fclose(binaryKernelRead);
    fclose(binaryMatrizWrite);

    matriz_destroy(matriz1);
    matriz_destroy(matriz2);

    return 0;
}