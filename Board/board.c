#include "board.h"
#include <string.h>
#include <ctype.h>


int board_init(board_t *board, size_t row, size_t col){
    if (!board)
        return 1;

    board->state = malloc(sizeof(char*) * row);
    if (!board->state)
        return 1;

    for (int i = 0; i < (int)row; i++) {

        board->state[i] = malloc(sizeof(char) * col);
        if (!board->state[i]) {
            free(board->state);
            return 1;
        }
    }

    board->rows = row;
    board->columns = col;

    return 0;
}

char board_get(board_t *board, unsigned int row, unsigned int col){
    if (row >= (unsigned int)board->rows || col >= (unsigned int)board->columns)
        return ' ';

    return board->state[row][col];
}

char board_get_round(board_t *board, int row, int col){

    if (row < 0)
        row = board->rows - 1;
    else
        row = row % board->rows;

    if (col < 0)
        col = board->columns - 1;
    else
        col = col % board->columns;

    return board->state[row][col];
}

int board_set(board_t *board, unsigned int row, unsigned int col, char val){
    if (row >= (unsigned int)board->rows || col >= (unsigned int)board->columns)
        return 1;

    board->state[row][col] = val;
    return 0;
}

int board_row_load(board_t *board, char *str, int rowNumber){
    char digArr[MAX_DIG];
    int numChar, rowEntry = 0, j = 0;

    for (int i = 0; str[i] != '\0'; i++){
        if (isdigit(str[i])) {      // Mientras sean digitos seguidos los agregamos al array de digitos
            digArr[j] = str[i];
            j++;
                
        } else if (str[i] == 'X' || str[i] == 'O') {
            digArr[j] = '\0';
            numChar = atoi(digArr);     // Convertimos los digitos a un numero
            j=0;

            if (rowEntry + numChar > board->columns)
                return 1;

            for (int k = 0; k < numChar; k++) {         // Colocamos numChar veces el caracter en la fila
                board->state[rowNumber][rowEntry] = str[i];
                rowEntry++;
            }

        } else if (str[i] != ' ' && str[i] != '\n' && str[i] != '\r')
            return 1;
    }
    
    if (rowEntry != board->columns)
        return 1;

    return 0;
}

 /*Definición de la estructura de datos del tablero 
void board_show(board_t board, char *res) {
    for (int i = 0; i < board.rows; i++) {
        for(int j = 0; j < board.columns; j++) {
            res[i * (board.columns + 1) + j] = board.state[i][j];
        }
        res[i * (board.columns + 1) + board.columns] = '\n';
    }
    res[((board.columns + 1) * board.rows) - 1] = '\0';
}



void board_show(board_t board, char *res) {
    int row, col, numChar = 1, resIndex = 0;
    char currentState, digArr[MAX_DIG];
     
    for (row = 0; row < board.rows; row++) {
        currentState = board.state[row][0];
        for (col = 0; col < board.columns; col++) {
            if (currentState == board.state[row][col]) {
                numChar++;
            } else {
                sprintf(digArr, "%d", numChar);
                printf("%s\n",digArr);
                numChar = 0;
                for(int i = 0; digArr[i] != '\0'; i++){
                    res[resIndex] = digArr[i];
                    resIndex++;
                }
                res[resIndex] = currentState;
                resIndex++;
                currentState = board.state[row][col];
            }
        }
        sprintf(digArr, "%d", numChar);
        numChar = 0;
        for(int i = 0; digArr[i] != '\0'; i++){
            res[resIndex] = digArr[i];
            resIndex++;
        }
        res[resIndex] = currentState;
        resIndex++;
        currentState = board.state[row][col];
        res[resIndex] = '\n';
        resIndex++;
    }
    res[resIndex] = '\0';
}*/

void board_show(board_t board, char *res){
    int cont = 0, k = 0;
    char caracter, digArr[MAX_DIG];
    for (int i = 0; i < board.columns; i++){
        for (int j = 0; board.state[i][j] != '\0'; j++ ){
            caracter = board.state[i][j];
            cont++;
            if ( board.state[i][j] != board.state[i][j+1]){
                sprintf(digArr, "%d", cont);
                strncat(res , digArr, strlen(digArr));

                res [k + strlen(digArr)] = caracter;
                k += strlen(digArr) + 1;
                cont = 0;
            }
        }
        res[k] ='\n';
        k++;
    }
    res[k] = '\0';
}

board_t* copy_board_init (board_t *board) {

    board_t* boardCopy = malloc(sizeof(board_t));

    if (board_init(boardCopy, board->rows, board->columns) != 0){
        free(boardCopy);
        return NULL;
    }

    return boardCopy;
}

void board_destroy(board_t *board){
    for (int i = 0; i < board->rows; i++){
        free(board->state[i]);
    }
    free(board->state);
    free(board);
}