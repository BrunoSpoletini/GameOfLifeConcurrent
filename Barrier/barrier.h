#ifndef BARRIER
#define BARRIER

#include <pthread.h>

/******************************************************************************/
/* Definición de la estructura de datos de la barrera */

typedef struct cond_barrier {
    unsigned int maxWait;
    unsigned int waiting;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} barrier_t;

/******************************************************************************/
/* Operaciones*/

/* Creación de una barrera de condición, tomando como argumento la cantidad de
hilos que se van a esperar*/
int barrier_init(barrier_t *barr, unsigned int count);

/* Función *bloqueante* para esperar a los demás hilos */
int barrier_wait(barrier_t *barr);

/* Eliminación de la barrera */
int barrier_destroy(barrier_t *barr);

#endif

