#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CHAIRS 3

int waiting = 0;
sem_t customers, barber;
pthread_mutex_t mutex;

void* barber_func(void* arg) {
    while(1) {
        sem_wait(&customers); // wait for customer

        pthread_mutex_lock(&mutex);
        waiting--;
        printf("Barber: Taking a customer, waiting = %d\n", waiting);
        pthread_mutex_unlock(&mutex);

        sem_post(&barber); // barber ready

        printf("Barber: Cutting hair...\n");
        sleep(2);
    }
}

void* customer_func(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);

    if(waiting < CHAIRS) {
        waiting++;
        printf("Customer %d: Sitting in waiting room (waiting=%d)\n", id, waiting);

        sem_post(&customers); // notify barber
        pthread_mutex_unlock(&mutex);

        sem_wait(&barber); // wait for barber
        printf("Customer %d: Getting haircut\n", id);
    } else {
        printf("Customer %d: No chair available → leaving\n", id);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t b, c[6];
    int id[6] = {1,2,3,4,5,6};

    printf("=== Sleeping Barber Problem ===\n");

    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&b, NULL, barber_func, NULL);

    for(int i = 0; i < 6; i++) {
        pthread_create(&c[i], NULL, customer_func, &id[i]);
        sleep(1);
    }

    for(int i = 0; i < 6; i++)
        pthread_join(c[i], NULL);

    return 0;
}
