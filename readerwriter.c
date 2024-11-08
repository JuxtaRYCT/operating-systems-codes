#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t resource;
pthread_mutex_t rmutex;
int reader_count = 0;

void* reader(void* arg) {
    while (1) {
        pthread_mutex_lock(&rmutex);
        reader_count++;
        if (reader_count == 1) {
            sem_wait(&resource);
        }
        pthread_mutex_unlock(&rmutex);

        printf("Reader %ld is reading the resource\n", (long)arg);
        sleep(1);

        pthread_mutex_lock(&rmutex);
        reader_count--;
        if (reader_count == 0) {
            sem_post(&resource);
        }
        pthread_mutex_unlock(&rmutex);

        sleep(1);
    }
}

void* writer(void* arg) {
    while (1) {
        printf("Writer %ld is waiting to write\n", (long)arg);
        sem_wait(&resource);

        printf("Writer %ld is writing to the resource\n", (long)arg);
        sleep(1);

        sem_post(&resource);

        sleep(1);
    }
}

int main() {
    pthread_t r_threads[5], w_threads[2];
    long i;

    sem_init(&resource, 0, 1);
    pthread_mutex_init(&rmutex, NULL);

    for (i = 0; i < 5; i++) {
        pthread_create(&r_threads[i], NULL, reader, (void*)i);
    }

    for (i = 0; i < 2; i++) {
        pthread_create(&w_threads[i], NULL, writer, (void*)i);
    }

    for (i = 0; i < 5; i++) {
        pthread_join(r_threads[i], NULL);
    }

    for (i = 0; i < 2; i++) {
        pthread_join(w_threads[i], NULL);
    }

    sem_destroy(&resource);
    pthread_mutex_destroy(&rmutex);

    return 0;
}
