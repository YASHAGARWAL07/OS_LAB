#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;

void* producer(void* arg) {
    int item = 1;

    for(int i = 0; i < 5; i++) {
        printf("\nProducer: Wants to produce item %d\n", item);

        pthread_mutex_lock(&mutex);

        while(count == SIZE) {
            printf("Producer: Buffer FULL → waiting...\n");
            pthread_cond_wait(&not_full, &mutex);
        }

        buffer[count++] = item;
        printf("Producer: Inserted %d, Buffer count = %d\n", item, count);

        pthread_cond_signal(&not_empty);
        printf("Producer: Signaled consumer\n");

        pthread_mutex_unlock(&mutex);

        item++;
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for(int i = 0; i < 5; i++) {
        printf("\nConsumer: Wants to consume\n");

        pthread_mutex_lock(&mutex);

        while(count == 0) {
            printf("Consumer: Buffer EMPTY → waiting...\n");
            pthread_cond_wait(&not_empty, &mutex);
        }

        int item = buffer[--count];
        printf("Consumer: Removed %d, Buffer count = %d\n", item, count);

        pthread_cond_signal(&not_full);
        printf("Consumer: Signaled producer\n");

        pthread_mutex_unlock(&mutex);

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    printf("=== Producer-Consumer using Mutex & Condition Variables ===\n");

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    printf("\n=== Execution Completed ===\n");

    return 0;
}

