#include "barrier.h"
#include "stdlib.h"
#include "stdio.h"

/* Creación de una barrera de condición, tomando como argumento la cantidad de
hilos que se van a esperar*/
int barrier_init(barrier_t *barr, unsigned int count){
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutexLock = PTHREAD_MUTEX_INITIALIZER;
    
    if(!barr)
        return 1;

    barr->maxWait = count - 1;
    barr->waiting = 0;
    barr->mutex = mutexLock;
    barr->cond = cond;

    return 0;
}

/* Función *bloqueante* para esperar a los demás hilos */
int barrier_wait(barrier_t *barr){
    int status;
    status = pthread_mutex_lock(&barr->mutex);
    if(status != 0)
        return 1;

    if (barr->waiting < barr->maxWait){
        barr->waiting++;
        status = pthread_cond_wait(&barr->cond, &barr->mutex);         // Deslockea el hilo actual del mutex y lo duerme bajo cond
        status = status || pthread_mutex_unlock(&barr->mutex);

    } else {     // Ultimo hilo
        barr->waiting = 0;
        status = pthread_cond_broadcast(&barr->cond);     // Despierta a los hilos bajo cond
        status = status || pthread_mutex_unlock(&barr->mutex);
    }

    return status;
}

/* Eliminación de la barrera */
int barrier_destroy(barrier_t *barr){
    int status;
    status = pthread_mutex_destroy (&barr->mutex);
    status = status || pthread_cond_destroy (&barr->cond);
    free(barr);

    return status;
}

