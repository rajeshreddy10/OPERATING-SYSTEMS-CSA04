#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
#define MAX_EATS 2  
pthread_mutex_t forks[NUM_PHILOSOPHERS];
void* philosopher(void* num) {
    int id = *(int*)num;
    for (int i = 0; i < MAX_EATS; i++) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 2);  
        pthread_mutex_lock(&forks[id]); 
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]); 
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2);
        pthread_mutex_unlock(&forks[id]); 
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]); 
    }
    printf("Philosopher %d has finished eating.\n", id);
    return NULL;
}
int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}