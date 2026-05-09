#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

void* task(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d: Wants to enter critical section\n", id);

    sem_wait(&mutex); // Lock
    printf("Thread %d: sem_wait() successful -> Entered critical section\n", id);

    printf("Thread %d: Performing critical operation...\n", id);
    sleep(2);

    printf("Thread %d: Leaving critical section\n", id);

    sem_post(&mutex); // Unlock
    printf("Thread %d: sem_post() called -> Other thread can enter now\n\n", id);

    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    printf("=== Demonstration of Semaphore Synchronization ===\n\n");

    sem_init(&mutex, 0, 1); // Only 1 thread allowed

    pthread_create(&t1, NULL, task, &id1);
    sleep(1); // Delay to clearly show blocking
    pthread_create(&t2, NULL, task, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&mutex);

    printf("\n=== Execution Completed ===\n");

    return 0;
}
