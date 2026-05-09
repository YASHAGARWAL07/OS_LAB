#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t forks[N];  // renamed from 'fork'

void* philosopher(void* arg) {
    int i = *(int*)arg;

    for(int j = 0; j < 2; j++) {
        printf("\nPhilosopher %d is THINKING\n", i);
        sleep(1);

        printf("Philosopher %d is HUNGRY\n", i);

        // Deadlock-free logic
        if(i % 2 == 0) {
            pthread_mutex_lock(&forks[i]); // LEFT
            printf("Philosopher %d picked LEFT fork %d\n", i, i);

            pthread_mutex_lock(&forks[(i+1)%N]); // RIGHT
            printf("Philosopher %d picked RIGHT fork %d\n", i, (i+1)%N);
        } else {
            pthread_mutex_lock(&forks[(i+1)%N]); // RIGHT
            printf("Philosopher %d picked RIGHT fork %d\n", i, (i+1)%N);

            pthread_mutex_lock(&forks[i]); // LEFT
            printf("Philosopher %d picked LEFT fork %d\n", i, i);
        }

        printf("Philosopher %d is EATING\n", i);
        sleep(1);

        pthread_mutex_unlock(&forks[i]);
        pthread_mutex_unlock(&forks[(i+1)%N]);

        printf("Philosopher %d released forks\n", i);
    }

    return NULL;
}

int main() {
    pthread_t p[N];
    int id[N];

    printf("=== Dining Philosophers (Deadlock-Free) ===\n");

    for(int i = 0; i < N; i++)
        pthread_mutex_init(&forks[i], NULL);

    for(int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(p[i], NULL);

    printf("\n=== Execution Completed ===\n");

    return 0;
}
