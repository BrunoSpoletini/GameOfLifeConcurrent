#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Creación del tablero */
int board_init(board_t *board, size_t col, size_t row){
    board = malloc(sizeof(board_t));
    board->estado = malloc(sizeof(char*) * col);
    for (int i = 0; i < col; i++){
        board->estado[i] = malloc(sizeof(char) * row);
    }
    return 0;
}

/* Creación del tablero con un elemento por default*/
int board_init_def(board_t *board, size_t col, size_t row, char def){
    board = malloc(sizeof(board_t));
    board->estado = malloc(sizeof(char*) * col);
    for (int i = 0; i < col; i++){
        board->estado[i] = malloc(sizeof(char) * row);
        for (int j = 0; j < row; j++){
            board->estado[i][j] = def;
        }
    }
    board_t *tablero;
    board_init(tablero, 10, 10);

    return 0;
}