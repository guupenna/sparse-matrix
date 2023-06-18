#ifndef LIST_H
#define LIST_H

enum mode {
    SPARSE,
    DENSE
};

enum list {
    ROW,
    COLUMN
};

enum operation {
    SUM,
    MULT
};

typedef float data_type;

typedef struct Node
{
    int row, column;
    data_type value;
    struct Node *nextRow;
    struct Node *nextColumn;
} Node;

typedef struct
{
    Node *head;
    int size;
} List;

// O(1) apenas operações constantes
Node * node_create(int row, int column, data_type value);

// O(1) apenas operações constantes
void node_destroy(Node *node);

// O(1) apenas operações constantes
int node_return_column(Node *node);

// O(1) apenas operações constantes
int node_return_row(Node *node);

// O(1) apenas operações constantes
data_type node_return_value(Node *node);

// O(1) apenas operações constantes
Node * node_return_nextColumn(Node *node);

// O(1) apenas operações constantes
Node * node_return_nextRow(Node *node);

// O(1) apenas operações constantes
List * list_create();

// O(n) linear, sendo n = número de linhas + número de colunas
void list_push(List *row, List *columns, Node *node);

// O(n) linear, sendo n = número de linhas + número de colunas
void list_push_middle(Node *node, Node *current, enum list);

// O(n) linear, sendo n = número de linhas + número de colunas
void list_remove(List *row, List *column, int rowIndex, int columnIndex);

// O(n) linear, sendo n = número de colunas
data_type list_read_node_value(List *row, int columnIndex);

// O(n^2) pois executa uma função de complexidade O(n) para cada node da lista
void list_operation(List **columnsResult, List *rowResult, List* row1, List *row2, enum operation);

// O(1) apenas operações constantes
Node * list_return_head(List *list);

// O(n) linear, sendo n = número de colunas
data_type list_return_sum(List *row);

// O(n) linear, sendo n = número de colunas
void list_write_binary(List *row, FILE *binary);

// O(n) linear, sendo n = número de colunas
void list_print_sparse(List *row, void (*printData)(data_type));

// O(n) linear, sendo n = número de colunas
void list_print_dense(List *row, int size, void (*printData)(data_type));

// O(n) linear, sendo n = número de colunas
void list_destroy_rows(List *row);

// O(1) apenas operações constantes
void list_destroy(List *list);

#endif