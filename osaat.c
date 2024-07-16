#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_variable = 0;
pthread_mutex_t lock;

void* thread_work(void* arg) {
    int id = *((int*)arg);
    printf("Thread %d starting...\n", id);

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&lock);
        shared_variable++;
        printf("Thread %d: Shared variable incremented to %d\n", id, shared_variable);
        pthread_mutex_unlock(&lock);

        usleep((rand() % 1000) * 1000);
    }

    printf("Thread %d finished.\n", id);
    free(arg); 
    return NULL;
}

int main() {
    int num_threads = 3;
    pthread_t threads[num_threads];

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init failed\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < num_threads; ++i) {
        int* id = malloc(sizeof(int)); 
        *id = i;
        if (pthread_create(&threads[i], NULL, thread_work, id) != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("All threads have finished.\n");
    printf("Final value of shared variable: %d\n", shared_variable);
    return 0;
}
