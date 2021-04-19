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
    if (!boardFile) {
        printf("No se encontro el archivo\n");
        return NULL;
    }

    if (fscanf(boardFile, "%d, %d, %d\n", nCycles, row, col) != 3)
        return NULL;

    if (board_init(board, col, row) != 0)
        return NULL;

    while (fscanf(boardFile, "%s\n", buffer) != EOF)
        strcat(rleArray,buffer);

    fclose(boardFile);

    if (board_load(board, rleArray) != 0)
        return NULL;

    game_t* game = malloc(sizeof(game_t));
    if (game) {
        game->board = board;
        game->cycles = nCycles;
    }

    return game;
}

void writeBoard(board_t board, const char *filename) {

    FILE *writeFile = fopen(filename, "w+");

    // BOARD SHOW
    for (int i = 0; i < board.columns; i++)
        fprintf(puntSalida, "%s\n", board.state[i]);

    fclose(writeFile);
    
}

board_t *conwayGoL(board_t *board, unsigned int cycles, const int nuproc) {
    pthread_t threads[nuproc];
    int status;
    void* res;
    barrier_t *barr;

    status = barrier_init(barr, nuproc);        // Inicio barrier
    if (status == 0){

        for (int i = 0; i < nuproc; i++)
            pthread_create(&threads[i], NULL, evolve, (void *)board );          // pasar parte del board y la barrier como el arg

        for (int i = 0; i < nuproc; i++)
            pthread_join(threads[i], &res);


    }

    barrier_destroy(barr);

    return board;

}

void* evolve() {
    // PARTE 1  procesar su parte 
    barrier_wait(barr);
    // PARTE 2  reescribir la nueva
    return NULL;
}

int main(int argc, char** argv) {

    game_t* simGoL = loadGame(argv[1]);

    if (!simGoL){
        printf("La creacion del juego fallo\n")
        return 0;
    }

    board_t* board = conwayGoL(simGoL->board, simGoL->cycles, get_nprocs());
    free(game_t);

    if (board){
        const char filename[1000];
        filename = strtok(argv[1], '.');
        writeBoard(board, filename);

        board_destroy(board);

    } else
        printf ("La simulacion del juego fallo\n")

    return 0;
}