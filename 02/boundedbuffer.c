/* bounded buffer example */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 20
#define NUMTEMS 30

typedef struct
{
    int item[BUFFER_SIZE];
    int totalitems;
    int in, out;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
} buffer_t;

//초기화해주는 부분.
buffer_t buf = {
    {0},
    0,
    0,0,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};

int produce_item()
{
    int item = (int) (100*rand() / (RAND_MAX+1.0) );
    sleep((unsigned long) (5.0*rand()/(RAND_MAX+1.0)));
    printf("produce_item: item=%d\n", item);
    return item;
}

int insert_item (int item)
{
    int status;

    //뮤텍스락
    status = pthread_mutex_lock (&buf.mutex);
    if(status != 0)
        return status;

    //버퍼의 총 개수가 버퍼수보다 더 많아지거나 status오류일때.???
    while (buf.totalitems >= BUFFER_SIZE && status == NULL )
    {   
        //삽입을 멈추고 기다린다.
        status = pthread_cond_wait (&buf.empty, &buf.mutex);            
    }
    if(status != 0)
    {   
        //status 정상값을 받으면 mutex를 unlock
        pthread_mutex_unlock (&buf.mutex);
        return status;
    }
    //실제 삽입하는 부분.
    buf.item[buf.in] = item;
    buf.in = (buf.in + 1) % BUFFER_SIZE ;
    buf.totalitems ++;

    if(status == pthread_cond_signal(&buf.full))
    {
        pthread_mutex_unlock(&buf.mutex);
        return status;
    }
    return pthread_mutex_unlock(&buf.mutex);
}

void consume_item (int item)
{
    sleep((unsigned long)(5.0*rand()/(RAND_MAX+1.0)));
    printf("\t\tconsume_item: item=%d\n", item);
}

int remove_item (int *temp)
{
    int status;
    status = pthread_mutex_lock(&buf.mutex);
    if(status != 0)
    {
        return status;
    }
    
    //쓰여진 데이터가 없다면.. 뮤텍스 wait
    while(buf.totalitems <= 0 && status == NULL)
    {
        status = pthread_cond_wait(&buf.full, &buf.mutex)
    }
}