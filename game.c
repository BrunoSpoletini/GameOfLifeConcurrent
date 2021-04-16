#include "game.h"
#include <stdlib.h>
#include <stdio.h>

/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename) {
    FILE *boardFile = fopen(filename, "r");

    fscanf(boardFile, "%d, %d, %d\n", ncycles, row, col);

    board_init(board_t *board, col, row);

    while (fscanf(boardFile, "%d %c\n", cant, state) != EOF) {
        

    }

}
