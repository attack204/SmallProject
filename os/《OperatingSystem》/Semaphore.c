#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <semaphore.h>
// #include "mythreads.h"

sem_t s;

void *dec(void *arg) {
    for(int i = 1; i <= 10; i++) {
        sem_wait(&s);
        printf("%d\n", i);
    }
}
void *add(void *arg) {
    //sem_post(&s);
}
int main(int argc, char *argv[])
{
    sem_init(&s, -1, -1);
    pthread_t p1, p2;
    pthread_create(&p1, NULL, dec, NULL);
   // pthread_create(&p2, NULL, add, NULL);
    pthread_join(p1, NULL);
   // pthread_join(p2, NULL);
    printf("end");
    return 0;
}