#ifndef GAME_TYPES
#define GAME_TYPES

#include "../Board/board.h"
#include "../Barrier/barrier.h"

#define MAX_LINE 10000

/******************************************************************************/
/* Representamos las células vivas como 'O' y las muertas como 'X' */

typedef enum _State {ALIVE = 'O', DEAD = 'X'} State;
/******************************************************************************/
/* Definición de la estructura de datos del game */

typedef struct _game {
    unsigned int cycles;
    board_t* board;
} game_t;

typedef struct _argsT {
    unsigned int cycles;
    unsigned int rowFrom;
    unsigned int rowTo;
    board_t* board;
    board_t* boardCopy;
    barrier_t* barrier;
} argsT_t;

/******************************************************************************/
/* Funciones del juego */

/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename);

/* Guardamos el tablero 'board' en el archivo 'filename' */
void writeBoard(board_t board, char *filename);

char next_state(board_t *board, int row, int col);

void* simT(void* argsT);

/* Simulamos el Juego de la Vida de Conway con tablero 'board' la cantidad de
ciclos indicados en 'cycles' en 'nuprocs' unidades de procesamiento*/
board_t *conwayGoL(board_t *board, unsigned int cycles, int nuproc);

#endif
