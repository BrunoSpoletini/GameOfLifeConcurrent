ARG = -Wall -Wextra -Werror -std=c99 -lpthread
BARRIER = ./Barrier/barrier
BOARD = ./Board/board
TEMP = barrier.o board.o simulador

all: simulador

interprete: game.c board.o barrier.o
	gcc $(ARG) -o simulador game.c board.o barrier.o -lm

barrier.o: $(BARRIER).c $(BARRIER).h
	gcc $(ARG) -c $(BARRIER).c 

board.o: $(BOARD).c $(BOARD).h
	gcc $(ARG) -c $(BOARD).c 

clean:
	-rm $(TEMP)

.PHONY : all
.PHONY : clean