#include <stdlib.h>
#include <stdio.h>

#include "../headers/list.h"

Node * node_create(int row, int column, data_type value)
{
    Node *node = (Node *)calloc(1, sizeof(Node));

    node->row = row;
    node->column = column;
    node->value = value;
    node->nextRow = NULL;
    node->nextColumn = NULL;

    return node;
}

void node_destroy(Node *node)
{
    free(node);
}

List * list_create()
{
    List *list = (List *)calloc(1, sizeof(List));

    list->head = NULL;
    list->size = 0;

    return list;
}

void list_push(List *row, List *column, Node *node)
{
    Node *current = row->head;

    if (row->head == NULL)
    {
        row->head = node;
    } else {
        // Condição que verifica se atribui antes do head
        if (row->head->column > node->column)
        {
            node->nextColumn = row->head;
            row->head = node;
        // Condição que verifica se atribui no mesmo lugar
        } else if (current->column == node->column) {
            current->value += node->value;
            node_destroy(node);
            return;
        } else {
            list_push_middle(node, current, ROW);
        }
    }
    row->size++;

    current = column->head;
    if (column->head == NULL)
    {
        column->head = node;
    } else {
        if (column->head->row > node->row)
        {
            node->nextRow = column->head;
            column->head = node;
        } else if (current->row != node->row) { 
            list_push_middle(node, current, COLUMN);
        }
    }
    column->size++;
}

void list_remove(List *row, List *column, int rowIndex, int columnIndex)
{
    Node *currentColumn = row->head, *currentRow = column->head, *prevRow = NULL, *prevColumn = NULL;

    if (row->head == NULL || column->head == NULL)
    {
        return;
    }

    while (currentRow)
    {
        if (currentRow->row == rowIndex)
        {
            break;
        } else {
            prevRow = currentRow;
            currentRow = currentRow->nextRow;
        }
    }

    while (currentColumn)
    {
        if (currentColumn->column == columnIndex)
        {
            if (prevColumn == NULL)
            {
                row->head = currentColumn->nextColumn;
            } else {
                prevColumn->nextColumn = currentColumn->nextColumn;
            }
            if (prevRow == NULL)
            {
                column->head = currentRow->nextRow;
            } else {
                prevRow->nextRow = currentRow->nextRow;
            }
            row->size--;
            column->size--;
            node_destroy(currentColumn);
            currentColumn = NULL;
        } else {
            prevColumn = currentColumn;
            currentColumn = currentColumn->nextColumn;
        }
    }
}

void list_push_middle(Node *node, Node *current, enum list list)
{
    switch(list)
    {
        case ROW:
        while (current)
        {
            if (current->nextColumn == NULL)
            {
                current->nextColumn = node;
                return;
            }
            if (current->nextColumn->column > node->column)
            {
                node->nextColumn = current->nextColumn;
                current->nextColumn = node;
                return;
            }
            current = current->nextColumn;
        }

        case COLUMN:
        while (current)
        {
            if (current->nextRow == NULL)
            {
                current->nextRow = node;
                return;
            }
            if (current->nextRow->row > node->row)
            {
                node->nextRow = current->nextRow;
                current->nextRow = node;
                return;
            }
            current = current->nextRow;
        }
    }
}

int index_has_node(List *row, int columnIndex)
{
    Node *node = row->head;

    if (row->head == NULL)
    {
        return 0;
    }

    while (node)
    {
        if (node->column == columnIndex)
        {
            return 1;
        }
    }
    
    return 0;
}

data_type list_read_node_value(List *row, int columnIndex)
{
    Node *node = row->head;

    while (node)
    {
        if (node->column == columnIndex)
        {
            return node->value;
        } else {
            node = node->nextColumn;
        }
    }

    return 0;
}

void list_operation(List **columnsResult, List *rowResult, List* row1, List *row2, enum operation operation)
{
    Node *node1 = row1->head, *node2 = row2->head, *nodeResult;

    while (node1 != NULL || node2 != NULL)
    {
        int columnIndex;
        if (node1 == NULL)
        {
            if (operation == MULT)
            {
                node2 = node2->nextColumn;
                continue;
            }
            columnIndex = node2->column;
            nodeResult = node_create(node2->row, node2->column, node2->value);
            node2 = node2->nextColumn;

            list_push(rowResult, columnsResult[columnIndex], nodeResult);
        } else if (node2 == NULL) {
            if (operation == MULT)
            {
                node1 = node1->nextColumn;
                continue;
            }
            columnIndex = node1->column;
            nodeResult = node_create(node1->row, node1->column, node1->value);
            node1 = node1->nextColumn;

            list_push(rowResult, columnsResult[columnIndex], nodeResult);
        } else if (node1->column < node2->column) {
            if (operation == MULT)
            {
                node1 = node1->nextColumn;
                continue;
            }
            columnIndex = node1->column;
            nodeResult = node_create(node1->row, node1->column, node1->value);
            node1 = node1->nextColumn;

            list_push(rowResult, columnsResult[columnIndex], nodeResult);
        } else if (node1->column > node2->column && operation == SUM) {
            if (operation == MULT)
            {
                node2 = node2->nextColumn;
                continue;
            }
            columnIndex = node2->column;
            nodeResult = node_create(node2->row, node2->column, node2->value);
            node2 = node2->nextColumn;

            list_push(rowResult, columnsResult[columnIndex], nodeResult);
        } else {
            columnIndex = node1->column;
            data_type value = 0;
            if (operation == SUM) value = node1->value + node2->value;
            if (operation == MULT) value = node1->value * node2->value;
            nodeResult = node_create(node1->row, node1->column, value);
            node1 = node1->nextColumn;
            node2 = node2->nextColumn;

            list_push(rowResult, columnsResult[columnIndex], nodeResult);
        }
    }
}

Node * list_return_head(List *list)
{
    return list->head;
}

int node_return_column(Node *node)
{
    return node->column;
}

int node_return_row(Node *node)
{
    return node->row;
}

data_type node_return_value(Node *node)
{
    return node->value;
}

Node * node_return_nextColumn(Node *node)
{
    return node->nextColumn;
}

Node * node_return_nextRow(Node *node)
{
    return node->nextRow;
}

data_type list_return_sum(List *row)
{
    Node *node = row->head;
    data_type value = 0;

    if (row->head == NULL)
    {
        return 0;
    }

    while (node)
    {
        value += node->value;
        node = node->nextColumn;
    }

    return value;
}

void list_write_binary(List *row, FILE *binary)
{
    Node *node = row->head;

    while (node)
    {
        fwrite(&node->row, sizeof(int), 1, binary);
        fwrite(&node->column, sizeof(int), 1, binary);
        fwrite(&node->value, sizeof(data_type), 1, binary);

        node = node->nextColumn;
    }
}

void list_print_sparse(List *row, void (*printData)(data_type))
{
    Node *node = row->head;

    while (node)
    {
        printf("\nLinha: ");
        printData(node->row);
        printf("\nColuna: ");
        printData(node->column);
        printf("\nValor: ");
        printData(node->value);
        printf("\n");

        node = node->nextColumn;
    }
}

void list_print_dense(List *row, int size, void (*printData)(data_type))
{
    Node *node = row->head;

    printf(" ");
    for (int count = 0; count < size; count++)
    {
        if (node == NULL)
        {
            printData(0);
            printf("    ");
            continue;
        } 
        if (node->column == count)
        {
            printData(node->value);

            // Formatação
            if (node->value < -99) printf(" ");
            else if (node->value < -9) printf("  ");
            else if (node->value < 0) printf("   ");
            else if (node->value < 10) printf("    ");
            else if (node->value < 100) printf("   ");
            else if (node->value < 1000) printf("  ");
            else printf(" ");

            node = node->nextColumn;
        } else {
            printData(0);
            printf("    ");
        }
    }
    printf("\n");
}

void list_destroy_rows(List *row)
{
    Node *node = row->head;

    while (node)
    {
        Node *next = node->nextColumn;
        node_destroy(node);
        node = next;
    }
    list_destroy(row);
}

void list_destroy(List *list)
{
    free(list);
}