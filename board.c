#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Creación del tablero */
int board_init(board_t *board, size_t col, size_t row){
    board = malloc(sizeof(board_t));
    if (!board)
        return 1;

    board->state = malloc(sizeof(char*) * row);
    if (!board->state)
        return 1;

    for (int i = 0; i < row; i++) {

        board->state[i] = malloc(sizeof(char) * col);
        if (!board->state[i])
            return 1;
    }

    board->rows = row;
    board->columns = col;

    return 0;
}

/* Creación del tablero con un elemento por default
int board_init_def(board_t *board, size_t col, size_t row, char def){
    if (board_init(board, col, row) != 0)
        return 1;

    for (int i = 0; i < col; i++){
        for (int j = 0; j < row; j++){
            board->state[i][j] = def;
        }
    }

    return 0;
}*/

/* Leer el tablero en una posición (col, row) 
char board_get(board_t board, unsigned int col, unsigned int row){
    return board.state[row][col];
}*/

/* Leer el tablero en una posición asumiendo que el tablero es 'redondo'.
char board_get_round(board_t board, int col, int row){
    return board.state[row % board.columns][col % board.columns];
}*/

/* Asignarle un valor 'val' a la posición (col, row) del tablero
int board_set(board_t board, unsigned int col, unsigned int row, char val){
    board.state[row % board.columns][col % board.columns] = val;
    return 0;
}*/


/* Leer de una lista de caracteres que codifican un tablero en formato RLE e
   interpretarla como un tablero 
int board_load(board_t *board, char *str){
    int numCaracteres;
    char caracter;
    for (int i = 0; str[0] != '\0'; str = strchr(str,caracter) + 1){
        sscanf(str, "%d%c", &numCaracteres, &caracter);  //Si se lee separado por \n se tiene que agregar aca "%d%c\n"
        printf("%d %c \n", numCaracteres, caracter);
    }

    return 0;
}*/

/* Leer de una lista de caracteres que codifican un tablero en formato RLE e
   interpretarla como una fila del tablero*/
int board_row_load(board_t *board, char *str, int rowNumber){
    int numChar = 0, rowEntry = 0;

    for (int i = 0; str[i] != '\0'; i++){
        if (isdigit(str[i])){
            if (isdigit(str[i+1]))
                numChar += 10 * (str[i] - '0');
            else    
                numChar += (str[i] - '0');
                
        } else if (str[i] == 'X' || str[i] == 'O') {
            if (rowEntry + numChar > board->columns)
                return 1;

            for (; rowEntry < numChar; rowEntry++)
                board->state[rowNumber][rowEntry] = str[i];
            numChar = 0;

        } else if (str[i] != ' ')
            return 1;
    }

    return 0;
}

/* Función para mostrar el tablero */
/* La función 'board_show' asume que hay espacio suficiente en 'res' para alojar el tablero.
void board_show(board_t board, char *res){
    int cont = 0, k = 0;
    char caracter, resultado[TAM_MAX], buff[TAM_MAX];
    strcpy(resultado, "");
    for (int i = 0; i < board.row; i++){
        for (int j = 0; board.state[i][j] != '\0'; j++ ){
            caracter = board.state[i][j];
            cont++;
            if ( board.state[i][j] != board.state[i][j+1]){
                sprintf(buff, "%d", cont);
                strncat(resultado , buff, strlen(buff));

                resultado [k + strlen(buff)] = caracter;
                k += strlen(buff) + 1;
                cont = 0;
            }
        }
        resultado[k] ='\n';
        k++;
    }
    resultado[k] = '\0';
    printf ("%s\n", resultado);
}*/

/* Destroy board */
void board_destroy(board_t *board){
    for (int i = 0; i < board->rows; i++){
        free(board->state[i]);
    }
    free(board->state);
    free(board);
}

/*int main (){
    char res[TAM_MAX];

    board_t *tablero;

    tablero = board_init_def(tablero, 5, 5, 'X');
    
    board_set(*tablero, 101, 1200, 'Z');

    //printf("%c\n", board_get_round(*tablero, 101, 1200));
    
    //char texto[]="10C20T420D";

    //printf("%s", strchr(texto,'C')  + 1);

    //board_load(tablero, texto);

    board_show(*tablero, res);

    board_destroy(tablero);

    //gcc board.c board.h && ./a.out 

    return 0;
}*/