#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_MAX 50000

/* Creación del tablero */
board_t *board_init(board_t *board, size_t col, size_t row){
    board = malloc(sizeof(board_t));
    board->estado = malloc(sizeof(char*) * col);
    board->rows = row;
    board->columns = col;
    for (int i = 0; i < col; i++){
        board->estado[i] = malloc(sizeof(char) * row);
    }
    return board;
}

/* Creación del tablero con un elemento por default*/
board_t *board_init_def(board_t *board, size_t col, size_t row, char def){
    board = board_init(board, col, row);
    for (int i = 0; i < col; i++){
        for (int j = 0; j < row; j++){
            board->estado[i][j] = def;
        }
    }
    return board;
}

/* Leer el tablero en una posición (col, row) */
char board_get(board_t board, unsigned int col, unsigned int row){
    return board.estado[col][row];
}

/* Leer el tablero en una posición asumiendo que el tablero es 'redondo'.*/
char board_get_round(board_t board, int col, int row){
    return board.estado[col % board.columns][row % board.columns];
}

/* Asignarle un valor 'val' a la posición (col, row) del tablero*/
void board_set(board_t board, unsigned int col, unsigned int row, char val){
    board.estado[col % board.columns][row % board.columns] = val;
}

/* Leer de una lista de caracteres que codifican un tablero en formato RLE e
   interpretarla como un tablero */
void board_load(board_t *board, char *str){
    int numCaracteres;
    char caracter;
    for (int i = 0; str[0] != '\0'; str = strchr(str,caracter) + 1){
        sscanf(str, "%d%c", &numCaracteres, &caracter);  //Si se lee separado por \n se tiene que agregar aca "%d%c\n"
        printf("%d %c \n", numCaracteres, caracter);
    }
}

/* Función para mostrar el tablero */
/* La función 'board_show' asume que hay espacio suficiente en 'res' para alojar el tablero.*/
void board_show(board_t board, char *res){
    int cont = 0, k = 0;
    char caracter, resultado[TAM_MAX], buff[TAM_MAX];
    strcpy(resultado, "");
    for (int i = 0; i < board.columns; i++){
        for (int j = 0; board.estado[i][j] != '\0'; j++ ){
            caracter = board.estado[i][j];
            cont++;
            if ( board.estado[i][j] != board.estado[i][j+1]){
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
}

/* Destroy board */
void board_destroy(board_t *board){
    for (int i = 0; i < board->columns; i++){
        free(board->estado[i]);
    }
    free(board->estado);
    free(board);
}

int main (){
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
}