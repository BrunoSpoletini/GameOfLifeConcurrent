#include "barrier.h"

/* Creación de una barrera de condición, tomando como argumento la cantidad de
hilos que se van a esperar*/
int barrier_init(barrier_t *barr, unsigned int count){
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutexLock = PTHREAD_MUTEX_INITIALIZER;
    barr = malloc(sizeof(barrier_t));
    barr->count = count;
    barr->waiting = 0;
    barr->mutex = mutexLock;
    barr->cond = cond;
}

/* Función *bloqueante* para esperar a los demás hilos */
int barrier_wait(barrier_t *barr){
    pthread_mutex_lock(barr->mutex);

    if (barr->waiting < barr->count){
        barr->waiting++;
        pthread_cond_wait(barr->cond, barr->mutex);
    } else {
        pthread_cond_broadcast(barr->cond);
    }

    pthread_mutex_unlock(barr->mutex);

}

/* Eliminación de la barrera */
int barrier_destroy(barrier_t *barr){
    pthread_mutex_destroy (barr->mutex);
    pthread_cond_destroy (barr->cond);
    free(barr);
}
