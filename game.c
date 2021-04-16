#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename) {

    board_t* board;
    int nCycles, row, col;
    char buffer[1000], rleArray[5000];

    FILE *boardFile = fopen(filename, "r");

    fscanf(boardFile, "%d, %d, %d\n", nCycles, row, col);

    board_init(board, col, row);

    while (fscanf(boardFile, "%s\n", buffer) != EOF)
        strcat(rleArray,buffer);

    fclose(boardFile);

    board_load(board, rleArray);

}

void writeBoard(board_t board, const char *filename) {

    FILE *writeFile = fopen(filename, "w+");
    for (int i = 0; i < board.columns; i++)
        fprintf(puntSalida, "%s\n", board.estado[i]);

    fclose(writeFile);
    
}

board_t *congwayGoL(board_t *board, unsigned int cycles, const int nuproc) {

}