#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
sem_t prod_limit, cons_limit;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int id = *(int*)arg;

    for(int i = 0; i < 5; i++) {
        sem_wait(&prod_limit); // limit producers
        printf("Producer %d: Allowed to produce\n", id);

        sem_wait(&empty); // wait if buffer full
        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        printf("Producer %d: Produced %d at %d\n", id, i, in);

        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sem_post(&prod_limit); // release producer slot
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;

    for(int i = 0; i < 5; i++) {
        sem_wait(&cons_limit); // limit consumers
        printf("Consumer %d: Allowed to consume\n", id);

        sem_wait(&full); // wait if buffer empty
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer %d: Consumed %d from %d\n", id, item, out);

        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sem_post(&cons_limit); // release consumer slot
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p[3], c[3];
    int id[3] = {1,2,3};

    printf("=== Producer Consumer with Limits (Max 3 each) ===\n");

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    sem_init(&prod_limit, 0, 3); // max 3 producers
    sem_init(&cons_limit, 0, 3); // max 3 consumers

    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < 3; i++) {
        pthread_create(&p[i], NULL, producer, &id[i]);
        pthread_create(&c[i], NULL, consumer, &id[i]);
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(p[i], NULL);
        pthread_join(c[i], NULL);
    }

    return 0;
}
