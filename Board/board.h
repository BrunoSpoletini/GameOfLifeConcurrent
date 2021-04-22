#ifndef BOARD
#define BOARD

#include <stdlib.h>
#include <stdio.h>

#define MAX_AUX 100

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
int board_init(board_t *board, size_t row, size_t col);

/* Leer el tablero en una posición (col, row) */
char board_get(board_t *board, unsigned int row, unsigned int col);

/* Leer el tablero en una posición asumiendo que el tablero es 'redondo'.*/
char board_get_round(board_t *board, int row, int col);

/* Asignarle un valor 'val' a la posición (col, row) del tablero*/
int board_set(board_t *board, unsigned int row, unsigned int col, char val);

/* Coloca la representacion correspondiente de una linea en formato rle en 
la fila correspondiente en el tablero*/
int board_row_load(board_t *board, char *str, int rowNumber);

/* Crea una copia del tablero (sin sus entradas) */
board_t* copy_board_init (board_t *board);

/* Función para mostrar el tablero */
/* La función 'board_show' asume que hay espacio suficiente en 'res' para alojar el tablero.*/
void board_show(board_t board, char *res);

/* Destroy board */
void board_destroy(board_t *board);

#endif
