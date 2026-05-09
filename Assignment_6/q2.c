#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item = 1;

    while(1) {
        printf("\nProducer: Wants to produce item %d\n", item);

        sem_wait(&empty); // wait if buffer full
        printf("Producer: empty slot available (sem_wait on empty)\n");

        pthread_mutex_lock(&mutex); // critical section
        printf("Producer: Entered critical section\n");

        buffer[in] = item;
        printf("Producer: Inserted %d at position %d\n", item, in);

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        printf("Producer: Exiting critical section\n");

        sem_post(&full); // signal item available
        printf("Producer: sem_post(full) -> Consumer can consume\n");

        item++;
        sleep(2);
    }
}

void* consumer(void* arg) {
    while(1) {
        printf("\nConsumer: Wants to consume\n");

        sem_wait(&full); // wait if buffer empty
        printf("Consumer: item available (sem_wait on full)\n");

        pthread_mutex_lock(&mutex); // critical section
        printf("Consumer: Entered critical section\n");

        int item = buffer[out];
        printf("Consumer: Removed %d from position %d\n", item, out);

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        printf("Consumer: Exiting critical section\n");

        sem_post(&empty); // signal empty slot
        printf("Consumer: sem_post(empty) -> Producer can produce\n");

        sleep(3);
    }
}

int main() {
    pthread_t p, c;

    printf("=== Producer-Consumer Problem (Buffer Size = 5) ===\n");

    sem_init(&empty, 0, SIZE); // initially all empty
    sem_init(&full, 0, 0);     // initially none full
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
