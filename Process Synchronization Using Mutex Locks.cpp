#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
int sharedCounter = 0;

void *incrementCounter(void *arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);

        sharedCounter++;
        printf("Thread %d: Counter = %d\n", *(int *)arg, sharedCounter);

        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, incrementCounter, &id1);
    pthread_create(&t2, NULL, incrementCounter, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}
