#ifndef MATRIZ_H
#define MATRIZ_H

#include "../headers/list.h"

typedef struct
{
    int numberRows, numberColumns;
    List **rows;
    List **columns;
} Matriz;

// O(n) linear, sendo n = número de linhas + número de colunas
Matriz * matriz_create(int numberRows, int numberColumns);

// O(n) linear pois utiliza apenas uma função linear em sua estrutura, n = número de linhas + número de colunas
void matriz_set_value(Matriz *matriz, int rowIndex, int columnIndex, data_type value);

// O(n) linear pois utiliza apenas uma função linear em sua estrutura, n = número de nós da linha
data_type matriz_read_value(Matriz *matriz, int rowIndex, int columnIndex);

// O(n^3) pois executa uma função O(n^2) para cada linha da matriz
Matriz * matriz_sum(Matriz *matriz1, Matriz *matriz2);

// O(n^3) pois executa uma função O(n) para cada node da linha e itera pelas linhas da matriz repetindo o processo
Matriz *matriz_scalar_mult(Matriz *matriz, int scalar);

// O(n^3) pois executa uma função O(n^2) para cada linha da matriz
Matriz * matriz_dot_mult(Matriz *matriz1, Matriz *matriz2);

// O(n^3) pois executa uma função O(n) para cada node da linha e itera pelas linhas da matriz repetindo o processo
Matriz * matriz_swap_row(Matriz *matriz, int swapIndex1, int swapIndex2);

// O(n^3) pois executa uma função O(n) para cada node da linha e itera pelas linhas da matriz repetindo o processo
Matriz * matriz_swap_column(Matriz *matriz, int swapIndex1, int swapIndex2);

// O(n^3) pois executa uma função O(n) para cada node da linha e itera pelas linhas da matriz repetindo o processo
Matriz * matriz_slice(Matriz *matriz, int startRow, int startColumn, int endRow, int endColumn);

// O(n^3) pois executa uma função O(n) para cada node da linha e itera pelas linhas da matriz da matriz repetindo o processo
Matriz * matriz_transpose(Matriz *matriz);

// O(n^5) pois executa, para cada posição da matriz, ou seja, dentro de 2 loops, um conjunto de funções em que a maior complexidade dentre elas é O(n^3)
Matriz * matriz_convolution(Matriz *matriz, Matriz *kernel);

// O(n^3) pois a função de maior complexidade executada em sua estrutura é O(n^3)
data_type matriz_return_value_convolution(Matriz *submatriz, Matriz *kernel);

// O(n^2) pois executa uma função O(n) para cada linha da matriz
void matriz_print(Matriz *matriz, void (*printData)(data_type), enum mode);

// O(n^2) pois executa uma função O(n) para cada linha da matriz
void matriz_write_binary(Matriz *matriz, FILE *binary);

// O(n^2) pois executa uma função O(n) para cada linha da matriz
Matriz * matriz_read_binary(FILE *binary);

// O(n^2) pois executa uma função O(n) para cada linha da matriz
void matriz_destroy();

#endif