//Rafael Moutinho Tessarotto/ 42122521/ 04N12

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//definir número de filosofos
#define NUM_FILOSOFOS 5
//varável, vetor de thead, definir tamanho de vetor, semáforo
pthread_mutex_t garfos[NUM_FILOSOFOS];
//função acionada quando inicia thread do filosofo de pegar os garfos
void *filosofo(void *arg) {
    int id = *(int *)arg;
    int garfo_esquerdo = id;
    int garfo_direito = (id + 1) % NUM_FILOSOFOS;
//executado quando o thread está acionado
    while (1) {
        // Pensar (realize alguma ação)
        printf("Filósofo %d está pensando.\n", id);
        usleep(rand() % 1000000);

        // Pegar garfo esquerdo
        pthread_mutex_lock(&garfos[garfo_esquerdo]);
        printf("Filósofo %d pegou o garfo esquerdo.\n", id);

        // Pegar garfo direito
        pthread_mutex_lock(&garfos[garfo_direito]);
        printf("Filósofo %d pegou o garfo direito e está comendo.\n", id);
        usleep(rand() % 1000000);

        // Liberar garfos
        pthread_mutex_unlock(&garfos[garfo_esquerdo]);
        pthread_mutex_unlock(&garfos[garfo_direito]);
        printf("Filósofo %d terminou de comer e liberou os garfos.\n", id);
    }
}
//
int main() {
    pthread_t filosofos[NUM_FILOSOFOS];
    int ids[NUM_FILOSOFOS];
//
    // Inicializar mutexes para os garfos
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_mutex_init(&garfos[i], NULL);
    }

    // Criar threads para os filósofos
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&filosofos[i], NULL, filosofo, &ids[i]);
    }

    // Aguardar as threads terminarem (o programa nunca sai deste loop)
    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(filosofos[i], NULL);
    }
//
    return 0;
}
