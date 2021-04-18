#include "barrier.h"

/* Creación de una barrera de condición, tomando como argumento la cantidad de
hilos que se van a esperar*/
int barrier_init(barrier_t *barr, unsigned int count){
    barr = malloc(sizeof(barrier_t));
    barr->count = count;
    barr->waiting = 0;
    barr->state = False;
    pthread_mutex_t mutexLock = PTHREAD_MUTEX_INITIALIZER;
    barr->mutex = mutexLock;
}

/* Función *bloqueante* para esperar a los demás hilos */
int barrier_wait(barrier_t *barr){

}

/* Eliminación de la barrera */
int barrier_destroy(barrier_t *barr){

}

