#include <stdlib.h>
#include <stdio.h>

#include "../headers/matriz.h"

Matriz *matriz_create(int numberRows, int numberColumns)
{
    Matriz *matriz = (Matriz *)calloc(1, sizeof(Matriz));

    matriz->numberRows = numberRows;
    matriz->numberColumns = numberColumns;

    matriz->rows = (List **)calloc(numberRows, sizeof(List *));
    matriz->columns = (List **)calloc(numberColumns, sizeof(List *));

    int i;
    for (i = 0; i < numberRows; i++)
    {
        matriz->rows[i] = list_create();
    }
    for (i = 0; i < numberColumns; i++)
    {
        matriz->columns[i] = list_create();
    }

    return matriz;
}

void matriz_set_value(Matriz *matriz, int rowIndex, int columnIndex, data_type value)
{
    if (rowIndex < 0 || rowIndex >= matriz->numberRows)
    {
        exit(printf("ERRO: Índice inválido para linha."));
    }
    if (columnIndex < 0 || columnIndex >= matriz->numberColumns)
    {
        exit(printf("ERRO: Índice inválido para coluna.\n"));
    }

    List *row = matriz->rows[rowIndex];
    List *column = matriz->columns[columnIndex];
    
    if (value != 0)
    {
        Node *node = node_create(rowIndex, columnIndex, value);
        list_push(row, column, node);
    } else {
        list_remove(row, column, rowIndex, columnIndex);
    }
}

data_type matriz_read_value(Matriz *matriz, int rowIndex, int columnIndex)
{
    List *row = matriz->rows[rowIndex];

    data_type value = list_read_node_value(row, columnIndex);

    return value;
}

Matriz * matriz_sum(Matriz *matriz1, Matriz *matriz2)
{
    if (!(matriz1->numberRows == matriz2->numberRows && matriz1->numberColumns == matriz2->numberColumns))
    {
        printf("ERRO: Só é possível somar matrizes de mesma ordem.\n");
        exit(1);
    }

    Matriz *matrizAdd = matriz_create(matriz1->numberRows, matriz1->numberColumns);

    for (int i = 0; i < matriz1->numberRows; i++)
    {
        List **columnsMatrizAdd = matrizAdd->columns;
        List *rowMatrizAdd = matrizAdd->rows[i];
        List *rowMatriz1 = matriz1->rows[i];
        List *rowMatriz2 = matriz2->rows[i];

        list_operation(columnsMatrizAdd, rowMatrizAdd, rowMatriz1, rowMatriz2, SUM);
    }

    return matrizAdd;
}

Matriz * matriz_scalar_mult(Matriz *matriz, int scalar)
{
    Matriz *matrizScalar = matriz_create(matriz->numberRows, matriz->numberColumns);

    Node *node = NULL; 
    for (int rowIndex = 0; rowIndex < matriz->numberRows; rowIndex++)
    {
        node = list_return_head(matriz->rows[rowIndex]);

        while (node)
        {
            int columnIndex = node_return_column(node);
            data_type value = node_return_value(node)*scalar;

            matriz_set_value(matrizScalar, rowIndex, columnIndex, value);

            node = node_return_nextColumn(node);
        } 
    }

    return matrizScalar;
}

Matriz * matriz_dot_mult(Matriz *matriz1, Matriz *matriz2)
{
    if (!(matriz1->numberRows == matriz2->numberRows && matriz1->numberColumns == matriz2->numberColumns))
    {
        printf("ERRO: Só é multiplicar ponto a ponto matrizes de mesma ordem.\n");
        exit(1);
    }

    Matriz *matrizDot = matriz_create(matriz1->numberRows, matriz1->numberColumns);

    for (int i = 0; i < matriz1->numberRows; i++)
    {
        List **columnsMatrizDot = matrizDot->columns;
        List *rowMatrizDot = matrizDot->rows[i];
        List *rowMatriz1 = matriz1->rows[i];
        List *rowMatriz2 = matriz2->rows[i];

        list_operation(columnsMatrizDot, rowMatrizDot, rowMatriz1, rowMatriz2, MULT);
    }

    return matrizDot;
}

Matriz * matriz_swap_row(Matriz *matriz, int swapIndex1, int swapIndex2)
{
    if ((swapIndex1 < 0 || swapIndex1 >= matriz->numberRows) || (swapIndex2 < 0 || swapIndex2 >= matriz->numberRows))
    {
        exit(printf("ERRO: Índice inválido para linha.\n"));
    }

    Matriz *matrizSwap = matriz_create(matriz->numberRows, matriz->numberColumns);

    for (int rowIndex = 0; rowIndex < matriz->numberRows; rowIndex++)
    {
        Node *node = list_return_head(matriz->rows[rowIndex]);

        if (rowIndex == swapIndex1)
        {
            node = list_return_head(matriz->rows[swapIndex2]);
        }
        if (rowIndex == swapIndex2)
        {
            node = list_return_head(matriz->rows[swapIndex1]);
        }

        while (node)
        {
            int columnIndex = node_return_column(node);
            data_type value = node_return_value(node);
            matriz_set_value(matrizSwap, rowIndex, columnIndex, value);

            node = node_return_nextColumn(node);
        }
    }

    return matrizSwap;   
}

Matriz * matriz_swap_column(Matriz *matriz, int swapIndex1, int swapIndex2)
{
    Matriz *matrizSwap = matriz_create(matriz->numberRows, matriz->numberColumns);

    if ((swapIndex1 < 0 || swapIndex1 >= matriz->numberColumns) || (swapIndex2 < 0 || swapIndex2 >= matriz->numberColumns))
    {
        exit(printf("ERRO: Índice inválido para coluna.\n"));
    }

    for (int columnIndex = 0; columnIndex < matriz->numberColumns; columnIndex++)
    {
        Node *node = list_return_head(matriz->columns[columnIndex]);
        
        if (columnIndex == swapIndex1)
        {
            node = list_return_head(matriz->columns[swapIndex2]);
        }
        if (columnIndex == swapIndex2)
        {
            node = list_return_head(matriz->columns[swapIndex1]);
        }

        while (node)
        {
            int rowIndex = node_return_row(node);
            data_type value = node_return_value(node);
            matriz_set_value(matrizSwap, rowIndex, columnIndex, value);

            node = node_return_nextRow(node);
        }
    }

    return matrizSwap;   
}

Matriz * matriz_slice(Matriz *matriz, int startRow, int startColumn, int endRow, int endColumn)
{
    int numberRows = endRow - startRow + 1;
    int numberColumns = endColumn - startColumn + 1;
    Matriz *matrizSlice = matriz_create(numberRows, numberColumns);

    if (startRow < 0) startRow = 0;
    if (startColumn < 0) startColumn = 0;
    if (endRow >= matriz->numberRows) endRow = matriz->numberRows - 1;
    if (endColumn >= matriz->numberColumns) endColumn = matriz->numberColumns - 1;

    for (int rowIndex = startRow; rowIndex <= endRow; rowIndex++)
    {
        Node *node = list_return_head(matriz->rows[rowIndex]);

        if (node == NULL) continue;

        int columnIndex = node_return_column(node);
        while (columnIndex <= endColumn)
        {
            if (columnIndex >= startColumn)
            {
                data_type value = node_return_value(node);
                matriz_set_value(matrizSlice, rowIndex-startRow, columnIndex-startColumn, value);
            }
            
            node = node_return_nextColumn(node);

            if (node == NULL)
            {
                break;
            } else {
                columnIndex = node_return_column(node);
            }
        }
    }

    return matrizSlice;
}

Matriz * matriz_transpose(Matriz *matriz)
{
    Matriz *matrizTranspose = matriz_create(matriz->numberColumns, matriz->numberRows);

    Node *node = NULL;
    for (int rowIndex = 0; rowIndex < matriz->numberRows; rowIndex++)
    {
        node = list_return_head(matriz->rows[rowIndex]);

        while (node)
        {
            int columnIndex = node_return_column(node);
            data_type value = node_return_value(node);

            matriz_set_value(matrizTranspose, columnIndex, rowIndex, value);

            node = node_return_nextColumn(node);
        }
    }

    return matrizTranspose;
}

Matriz * matriz_convolution(Matriz *matriz, Matriz *kernel)
{
    if (kernel->numberRows % 2 == 0 || kernel->numberColumns % 2 == 0)
    {
        exit(printf("ERRO: O kernel precisa ter dimensões ímpares.\n"));
    }

    Matriz *matrizConvolution = matriz_create(matriz->numberRows, matriz->numberColumns);

    int rowKernel = kernel->numberRows / 2;
    int columnKernel = kernel->numberColumns / 2;

    for (int i = 0; i < matriz->numberRows; i++)
    {
        for (int j = 0; j < matriz->numberColumns; j++)
        {
            Matriz *submatriz = matriz_slice(matriz, i-rowKernel, j-columnKernel, i+rowKernel, j+columnKernel);

            data_type value = matriz_return_value_convolution(submatriz, kernel);

            matriz_set_value(matrizConvolution, i, j, value);

            matriz_destroy(submatriz);
        }
    }

    return matrizConvolution;
}

data_type matriz_return_value_convolution(Matriz *submatriz, Matriz *kernel)
{
    Matriz * matrizResult = matriz_dot_mult(submatriz, kernel);

    data_type value = 0;

    for (int i = 0; i < matrizResult->numberRows; i++)
    {
        value += list_return_sum(matrizResult->rows[i]);
    }

    matriz_destroy(matrizResult);

    return value;
}

void matriz_print(Matriz *matriz, void (*printData)(data_type), enum mode mode)
{
    switch(mode)
    {
        case SPARSE:
        for (int i = 0; i < matriz->numberRows; i++)
        {
            list_print_sparse(matriz->rows[i], printData);
        }
        break;

        case DENSE:
        for (int i = 0; i < matriz->numberRows; i++)
        {
            list_print_dense(matriz->rows[i], matriz->numberColumns, printData);
        }
        break;
    }
    printf("\n");
}

void matriz_write_binary(Matriz *matriz, FILE *binary)
{
    fwrite(&matriz->numberRows, sizeof(int), 1, binary);

    fwrite(&matriz->numberColumns, sizeof(int), 1, binary);

    for (int i = 0; i < matriz->numberRows; i++)
    {
        list_write_binary(matriz->rows[i], binary);
    }
}

Matriz * matriz_read_binary(FILE *binary)
{
    int numberRows, numberColumns;

    fread(&numberRows, sizeof(int), 1, binary);

    fread(&numberColumns, sizeof(int), 1, binary);

    Matriz *matriz = matriz_create(numberRows, numberColumns);

    int rowIndex, columnIndex;
    data_type value;

    while (fread(&rowIndex, sizeof(int), 1, binary) == 1)
    {
        fread(&columnIndex, sizeof(int), 1, binary);
        fread(&value, sizeof(data_type), 1, binary);
        matriz_set_value(matriz, rowIndex, columnIndex, value);
    }
    return matriz;
}

void matriz_destroy(Matriz *matriz)
{
    int i;
    for (i = 0; i < matriz->numberRows; i++)
    {
        list_destroy_rows(matriz->rows[i]);
    }
    for (i = 0; i < matriz->numberColumns; i++)
    {
        list_destroy(matriz->columns[i]);
    }

    free(matriz->rows);
    free(matriz->columns);
    free(matriz);
}