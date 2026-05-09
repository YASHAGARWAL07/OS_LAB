#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CONN 10
#define TOTAL_REQ 20   // We can increase to 100

sem_t db;

void* access_db(void* arg) {
    int id = *(int*)arg;

    printf("Request %d: Waiting for database connection...\n", id);

    sem_wait(&db); // acquire connection

    printf("Request %d: Connected to database\n", id);

    sleep(2); // simulate work

    printf("Request %d: Releasing database connection\n", id);

    sem_post(&db); // release connection

    return NULL;
}

int main() {
    pthread_t t[TOTAL_REQ];
    int id[TOTAL_REQ];

    printf("=== Database Connection Control (Max 10) ===\n");

    sem_init(&db, 0, MAX_CONN);

    for(int i = 0; i < TOTAL_REQ; i++) {
        id[i] = i + 1;
        pthread_create(&t[i], NULL, access_db, &id[i]);
    }

    for(int i = 0; i < TOTAL_REQ; i++)
        pthread_join(t[i], NULL);

    printf("\n=== All Requests Completed ===\n");

    return 0;
}
