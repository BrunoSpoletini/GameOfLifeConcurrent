#include "barrier.h"

/* Creación de una barrera de condición, tomando como argumento la cantidad de
hilos que se van a esperar*/
int barrier_init(barrier_t *barr, unsigned int count){
    barr = malloc(sizeof(barrier_t));
    barr->count = count;
    barr->waiting = 0;
    barr->state = False;
    pthread_mutex_t mutexLock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    barr->mutex = mutexLock;
    barr->cond = cond;
}

/* Función *bloqueante* para esperar a los demás hilos */
int barrier_wait(barrier_t *barr){
    if (barr->waiting < barr->count){
        barr->waiting++;
        pthread_mutex_lock(barr->mutex);
        pthread_cond_wait(barr->cond, barr->mutex);
        pthread_mutex_unlock(barr->mutex);
    } else {
        pthread_cond_broadcast(barr->cond);
    }

}

/* Eliminación de la barrera */
int barrier_destroy(barrier_t *barr){

}

