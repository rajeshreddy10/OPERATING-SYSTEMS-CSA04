#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>  

sem_t mutex, wrt;
int read_count = 0, data = 0;

void *writer(void *arg) {
    intptr_t id = (intptr_t)arg;  
    sem_wait(&wrt);
    data++;
    printf("Writer %ld writes data: %d\n", id, data);
    sem_post(&wrt);
    return NULL;
}

void *reader(void *arg) {
    intptr_t id = (intptr_t)arg;  
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %ld reads data: %d\n", id, data);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt);
    sem_post(&mutex);
    return NULL;
}

int main() {
    pthread_t r[5], w[2];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    for (intptr_t i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, (void *)i);

    for (intptr_t i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, (void *)i);

    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
