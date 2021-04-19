#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

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

    game_t* game->board = board;
    game_t* game->cycles = nCycles;

    return(game);
}

void writeBoard(board_t board, const char *filename) {

    FILE *writeFile = fopen(filename, "w+");
    for (int i = 0; i < board.columns; i++)
        fprintf(puntSalida, "%s\n", board.estado[i]);

    fclose(writeFile);
    
}

board_t *conwayGoL(board_t *board, unsigned int cycles, const int nuproc) {
    pthread_t threads[nuproc];
    void* res;
    barrier_init(barrier_t *barr, unsigned int count)
    for (int i = 0; i < nuproc; i++)
        pthread_create(&threads[i], NULL, evolve, (void *)board );

    for (int i = 0; i < nuproc; i++)
        pthread_join(threads[i], &res);

}

void* evolve() {
    
    return NULL;
}

int main(int argc, char** argv) {

    game_t* simGoL = loadGame(argv[1]);
    board_t* board = conwayGoL(simGoL->board, simGoL->cycles, get_nprocs());
    const char filename[1000];
    filename = strtok(argv[1], '.');
    writeBoard(board, filename);

    return 0;
}