#ifndef GAME_TYPES
#define GAME_TYPES
#include "board.h"
#include "barrier.h"

#define MAX_LINE 5000

/******************************************************************************/
/* Representamos las células vivas como 'O' y las muertas como 'X' */

enum State {ALIVE, DEAD};
/******************************************************************************/

typedef struct _game {
    unsigned int cycles;
    board_t* board;
} game_t;

/******************************************************************************/

/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename);

/* Guardamos el tablero 'board' en el archivo 'filename' */
void writeBoard(board_t board, const char *filename);

/* Simulamos el Juego de la Vida de Conway con tablero 'board' la cantidad de
ciclos indicados en 'cycles' en 'nuprocs' unidades de procesamiento*/
board_t *conwayGoL(board_t *board, unsigned int cycles, const int nuproc);

#endif
