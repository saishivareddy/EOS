#include<stdio.h>
#include<pthread.h>

int count =0;
pthread_mutex_t mutex_count;
pthread_mutexattr_t mutex_attr_count;

void *incThread(void *arg)
{
    while(1)
    {
      ;
        pthread_mutex_lock(&mutex_count);
         printf("Inc: Changing count\n");
        count++;
        printf("Inc :Sleeping\n");
        sleep(10);
        printf("Inc Thread: %d\n",count);
        pthread_mutex_unlock(&mutex_count);
        
    }
}
void *decThread(void *arg)
{
    int res = 0;
    while(1)
    {
        res=pthread_mutex_trylock(&mutex_count);
        printf("Result : %d\n", res);
        count--;
        printf("Dec Thread: %d\n",count);
        pthread_mutex_unlock(&mutex_count);
    }
}
int main()
{
    pthread_t inc,dec;
    pthread_mutexattr_init(&mutex_attr_count);
    pthread_mutexattr_settype(&mutex_attr_count, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutex_count, &mutex_attr_count);

    pthread_create(&inc,NULL,incThread,NULL);
    pthread_create(&dec,NULL,decThread,NULL);

    pthread_join(inc,NULL);
    pthread_join(dec,NULL);

    pthread_mutex_destroy(&mutex_count);
    return 0;
}