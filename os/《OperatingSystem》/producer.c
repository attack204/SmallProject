#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

const int loops = 10;
int count = 0;
int buffer;
pthread_cond_t empty, fill;
pthread_mutex_t mutex;

void put(int value)
{
    assert(count == 0);
    count = 1;
    buffer = value;
    return ;
}

int get()
{
    assert(count == 1);
    count = 0;
    return buffer;
}

void *producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mutex);
        printf("thread1 i: %d\n", i);
        while (count == 1)
            pthread_cond_wait(&empty, &mutex);
        put(i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        pthread_mutex_lock(&mutex);
        printf("thread2 i: %d\n", i);
        while (count == 0)
            pthread_cond_wait(&fill, &mutex);
        int tmp = get();
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("%d\n", tmp);
    }
}

int main()
{
    pthread_t p1, p2;
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, consumer, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("finished");
}