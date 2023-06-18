#include <stdio.h>
#include <stdlib.h>

#include "headers/matriz.h"

void printData(data_type data)
{
    printf("%.0f", data);
}

int main(int argc, char *argv[])
{
    int numberRows, numberColumns, value, rowIndex, columnIndex;
    Matriz *matriz;
    FILE *binaryMatrizWrite;
    char caminho[100];

    if (argc <= 1)
    {
        exit(printf("ERRO: O caminho para o arquivo binário não foi informado.\n"));
    }

    sprintf(caminho, "binary/%s.bin", argv[1]);
    binaryMatrizWrite = fopen(caminho, "wb");

    if (binaryMatrizWrite == NULL)
    {
        exit(printf("ERRO: Não foi possível abrir o arquivo com o caminho %s para escrita\n", argv[1]));
    }

    printf("Digite o número de linhas: ");
    scanf("%d", &numberRows);

    printf("Digite o número de colunas: ");
    scanf("%d", &numberColumns);

    matriz = matriz_create(numberRows, numberColumns);

    int numberValues;
    printf("\nDigite a quantidade de valores a serem colocados na matriz: ");
    scanf("%d", &numberValues);

    for (int i = 0; i < numberValues; i++)
    {
        printf("\n\n- %dº valor", i+1);

        printf("\nDigite a linha: ");
        scanf("%d", &rowIndex);

        printf("Digite a coluna: ");
        scanf("%d", &columnIndex);

        printf("Digite o valor: ");
        scanf("%d", &value);

        matriz_set_value(matriz, rowIndex, columnIndex, value);
    }

    matriz_print(matriz, printData, SPARSE);
    matriz_print(matriz, printData, DENSE);

    scanf("%d %d", &rowIndex, &columnIndex);

    matriz_write_binary(matriz, binaryMatrizWrite);

    fclose(binaryMatrizWrite);
    
    matriz_destroy(matriz);

    return 0;
}