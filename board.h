#ifndef BOARD
#define BOARD

#include <stdlib.h>
#include <stdio.h> //BORRAR TESTEO

#define MAX_DIG 1000

/******************************************************************************/
/* Definición de la estructura de datos del tablero */

typedef struct _board {
    char **state;
    int rows;
    int columns;
} board_t;

/******************************************************************************/
/* Funciones sobre el tablero */

/* Creación del tablero */
int board_init(board_t *board, size_t col, size_t row);

/* Leer el tablero en una posición (col, row) */
char board_get(board_t board, unsigned int col, unsigned int row);

/* Leer el tablero en una posición asumiendo que el tablero es 'redondo'.*/
char board_get_round(board_t board, int col, int row);

/* Asignarle un valor 'val' a la posición (col, row) del tablero*/
int board_set(board_t board, unsigned int col, unsigned int row, char val);

/* Coloca la representacion correspondiente de una linea en formato rle en 
la fila correspondiente en el tablero*/
int board_row_load(board_t *board, char *str, int rowNumber);

/* Destroy board */
void board_destroy(board_t *board);

#endif
