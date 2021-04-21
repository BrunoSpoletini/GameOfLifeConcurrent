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

char next_state(board_t *board, row, col) {
    State currentState = board->state[row][col];
    int i, j, aliveAround = 0;

    for (i = row - 1; i < row + 1 && aliveAround <= 4; i++) {
        for (j = col - 1; i < col + 1 && aliveAround <= 4; j++) {
            if (i != row && j != col){
                if (board_get_round(board, i, j) == ALIVE)
                    aliveAround += 1;
            }
        }
    }

    if (currentState == ALIVE && aliveAround != 2 && aliveAround != 3)
        currentState = DEAD;

    if (currentState == DEAD && aliveAround == 3)
        currentState = ALIVE;

    return currentState;
}

void* simT(void argsT) {
    unsigned int rowFrom = ((argsT_t*)argsT)->rowFrom;
    unsigned int rowTo = ((argsT_t*)argsT)->rowTo;
    unsigned int cycles = ((argsT_t*)argsT)->cycles;
    board_t *board = ((argsT_t*)argsT)->board;
    board_t *boardCopy = ((argsT_t*)argsT)->boardCopy;
    board_t *readBoard, *writeBoard;
    barrier *barr = ((argsT_t*)argsT)->barrier;

    int ncycle, i, j;
    for (ncycle; ncycle < cycles; ncycle++){
        readBoard = ncycle % 2 == 0 ? board : boardCopy;
        writeBoard = ncycle % 2 == 0 ? boardCopy : board;

        for (i = rowFrom; i <= rowTo; i++){
            for (j = 0; j < board->columns; j++){
                board_set(writeBoard, i, j, next_state(readBoard, i, j));
            }
        }

        barrier_wait(barr);
    } 

    return NULL;
}

board_t *conwayGoL(board_t *board, unsigned int cycles, const int nuproc) {
    int status;
    void* res;
    barrier_t *barr;

    if (nuproc > board->rows)
        nuproc = board->rows;

    pthread_t threads[nuproc];

    status = barrier_init(barr, nuproc);        // Inicio barrier
    if (status != 0) {
        perror("Fallo al iniciar la barrera");
        board_destroy(board);
        return NULL;
    }    

    int rowsPerT = board->rows / nuproc;
    int extraRows = board->rows % nuproc;
    int addRow = 0;
    board_t* boardCopy = copy_board_init(board);
    argsT_t argsT[nuproc];

    for (int i = 0; i < nuproc; i++){
        argsT[i].cycles = cycles;
        argsT[i].board = board;
        argsT[i].boardCopy = boardCopy
        argsT[i].barrier = barr;

        argsT[i].rowFrom = (rowsPerT * i) + addRow;

        if (extraRows > 0) {
            addRow++;
            extraRows--;
        }           
        
        argsT[i].rowTo = (rowsPerT * (i + 1)) + addRow;
    }


    for (int i = 0; i < nuproc; i++)
        pthread_create(&threads[i], NULL, simT, (void *)argsT[i]);          // pasar parte del board y la barrier como el arg

    for (int i = 0; i < nuproc; i++)
        pthread_join(threads[i], &res);

    barrier_destroy(barr);

    return cycles % 2 == 0 ? board : boardCopy;

}