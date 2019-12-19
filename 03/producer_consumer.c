/*3. 쓰레드를 사용하여 생산자 소비자 문제를 해결하는 
제한 버퍼(Bounded Buffer)를 생성하고 활용하는 프로그램을 구현하시오.*/
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 10

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
    1,1,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER
};

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
    printf("put item %d in buf[%d]\n", buf.item[buf.in-1], buf.in-1);

    if(status == pthread_cond_signal(&buf.full))
    {
        pthread_mutex_unlock(&buf.mutex);
        return status;
    }
    return pthread_mutex_unlock(&buf.mutex);
}

int remove_item ()
{
    int temp;
    int status;
    status = pthread_mutex_lock(&buf.mutex);
    if(status != 0)
    {
        return status;
    }
    
    //쓰여진 데이터가 없다면.. 뮤텍스 wait
    while(buf.totalitems <= 0 && status == NULL)
    {
        status = pthread_cond_wait(&buf.full, &buf.mutex);
    }
    if(status != 0)
    {
        pthread_mutex_unlock(&buf.mutex);
        return status;
    }
    
    temp = buf.item[buf.out];
    buf.out = (buf.out + 1) % BUFFER_SIZE;
    buf.totalitems--;
    //printf("                print buf[%d] = %d\n", buf.out-1, temp);
    printf("                %d X %d = %d\n", temp, buf.out-1, temp * (buf.out-1));

    if(status = pthread_cond_signal(&buf.empty))
    {
        pthread_mutex_unlock(&buf.mutex);
        return status;
    }

    return pthread_mutex_unlock(&buf.mutex);

}

void * producer(void *arg)
{
    int item = (int)arg;
    printf("item값 : %d\n", item);
    while (1)
    {
        insert_item(item);
    }
}

void* consumer(void *arg)
{
    while (1)
    {
        sleep(1);
        remove_item();
    }    
}

void main()
{
    int status;
    void *result;
    pthread_t producer_tid, consumer_tid;
    /*쓰레드 생성*/

    int gugu;
    printf("구구단을 출력하는 프로그램입니다.\n");
    printf("몇단을 출력하시겠습니까? ");
    scanf("%d", &gugu);
    

    status = pthread_create(&producer_tid, NULL, producer, gugu);
    if(status != 0)
    {
        perror("create producer thread");
    }
    status = pthread_create(&consumer_tid, NULL, consumer, NULL);
    if(status != 0)
    {
        perror("create consumer thread");
    }

    status = pthread_join(producer_tid, NULL);
    if(status != 0)
    {
        perror("JOIN producer thread");
    }
    status = pthread_join(consumer_tid, NULL);
    if(status != 0)
    {
        perror("JOIN consumer thread");
    }
}