#include "./Game/game.h"

int main(int argc, char** argv) {

    game_t* simGoL = loadGame(argv[1]);

    if (!simGoL){
        perror("La creacion del juego fallo\n");
        return 0;
    }

    board_t* board = conwayGoL(simGoL->board, simGoL->cycles, get_nprocs());
    free(simGoL);

    if (board){
        char* filename;
        filename = strtok(argv[1], ".");
        writeBoard((*board), filename);

        board_destroy(board);

    } else
        perror("La simulacion del juego fallo\n");

    return 0;
}
