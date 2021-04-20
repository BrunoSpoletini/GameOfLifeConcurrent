#include "board.h"
#include <string.h> // atoi()
#include <ctype.h> // isdigit()


int board_init(board_t *board, size_t row, size_t col){
    if (!board)
        return 1;

    board->state = malloc(sizeof(char*) * row);
    if (!board->state)
        return 1;

    for (int i = 0; i < row; i++) {

        board->state[i] = malloc(sizeof(char) * col);
        if (!board->state[i]){
            free(board->state);
            return 1;
        }
    }

    board->rows = row;
    board->columns = col;

    return 0;
}

char board_get(board_t board, unsigned int row, unsigned int col){
    if (row >= board.rows || col >= board.columns)
        return ' ';

    return board.state[row][col];
}

char board_get_round(board_t board, int row, int col){
    row = row % board.rows;
    col = col % board.rows;

    if (row < 0)
        row += board.rows;

    if (col < 0)
        col += board.columns;

    return board.state[row][col];
}

int board_set(board_t board, unsigned int row, unsigned int col, char val){
    if (row >= board.rows || col >= board.columns)
        return 1;

    board.state[row][col] = val;
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

void board_destroy(board_t *board){
    for (int i = 0; i < board->rows; i++){
        free(board->state[i]);
    }
    free(board->state);
    free(board);
}