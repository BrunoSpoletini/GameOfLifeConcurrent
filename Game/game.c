#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>


/* Cargamos el juego desde un archivo */
game_t *loadGame(const char *filename) {

    int nCycles, row, col, invalidRle = 0;
    char line[MAX_LINE];

    FILE *boardFile = fopen(filename, "r");
    if (!boardFile) {
        perror("No se encontro el archivo\n");
        return NULL;
    }

    if (fscanf(boardFile, "%d %d %d\n", &nCycles, &row, &col) != 3)
        invalidRle = 1;
    
    board_t* board = malloc(sizeof(board_t));
    if (board_init(board, row, col) != 0){
        fclose(boardFile);
        free(board);
        return NULL;
    }

    int rowNumber = 0;
    for (; fgets(line, MAX_LINE, boardFile) && invalidRle == 0; rowNumber++){

        if (rowNumber >= row)
            invalidRle = 1;

        if (invalidRle == 0)
            invalidRle = board_row_load(board, line, rowNumber);

    }

    if (rowNumber != row)
        invalidRle = 1;

    if (invalidRle != 0){
        perror("Alguna linea del archivo es invalida\n");
        board_destroy(board);
        fclose(boardFile);
        return NULL;
    }

    fclose(boardFile);

    game_t* game = malloc(sizeof(game_t));
    if (game) {
        game->board = board;
        game->cycles = nCycles;
    }

    return game;
}

void writeBoard(board_t board, char *filename) {

    FILE *writeFile = fopen(strcat(filename,".final"), "w+");
    if (!writeFile)
        perror("Fallo escritura del archivo\n");

    for (int i = 0; i < board.rows; i++)
        fprintf(writeFile, "%s\n", board.state[i]);

    fclose(writeFile);
    
}

board_t *conwayGoL(board_t *board, unsigned int cycles, const int nuproc) {
    pthread_t threads[nuproc];
    int status;
    void* res;
    barrier_t *barr;

    status = barrier_init(barr, nuproc);        // Inicio barrier
    if (status != 0) {
        perror("Fallo al iniciar la barrera");
        board_destroy(board);
        return NULL;
    }    

    int rowsPerT = board->rows / nuproc;
    int extraRows = board->rows % nuproc;
    for (int i = 0; i < nuproc; i++) {
        board_t* boardT = malloc(sizeof(board_t));
        board_init (boardT,board->columns,)
        tArgs[i][0] = boardT*
        board_init(boartT)
        tArgs[i][1] = barr;
    }


    for (int i = 0; i < nuproc; i++)
        pthread_create(&threads[i], NULL, evolve, (void *)args );          // pasar parte del board y la barrier como el arg

    for (int i = 0; i < nuproc; i++)
        pthread_join(threads[i], &res);

    barrier_destroy(barr);

    return board;

}

void* evolve() {
    // PARTE 1  procesar su parte 
    barrier_wait(barr);
    // PARTE 2  reescribir la nueva
    return NULL;
}

