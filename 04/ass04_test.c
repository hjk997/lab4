#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define MSG_SIZE 1024

typedef struct {
char message[MSG_SIZE]; // 서버 - 클라이언트가 공유하는 메시지 버퍼 
int client_code; // 쓰레드 코드
int receive_count;
int flag;
pthread_mutex_t mutex; // 뮤택스 락
pthread_cond_t send; // 클라이언트가 메시지를 보낸 상태
pthread_cond_t call; // 서버가 메시지를 전송한 상태 
pthread_cond_t receive; // 서버가 메시지를 전송한 상태 
} buffer_t;

buffer_t bb = { "Thread Message", 0, 0, 0,
PTHREAD_MUTEX_INITIALIZER,
PTHREAD_COND_INITIALIZER,
PTHREAD_COND_INITIALIZER,
PTHREAD_COND_INITIALIZER};

void call_item();
void * sender();
void * receiver();
void send_item();
void receive_item();

void * sender(){ // server
	while (1) {
		send_item();
		sleep(5.0);
	}
}

void * receiver(void *arg) { // client
	float randtime;
	while (1) {
		call_item(arg); // 메시지 전송 요청
		receive_item (arg); // 메시지 받음
		randtime = rand()%2 +1.0;
		sleep(randtime);
	}
}

void send_item(){ // send message in server
	int status;
	
	status = pthread_mutex_lock (&bb.mutex);
	while(bb.flag != 1 ){
		status = pthread_cond_wait (&bb.call, &bb.mutex);
	}
	
	if (status != 0) {
		return status;
	}

	if (status = pthread_cond_broadcast(&bb.receive)) {
		return status;
	}

	printf("------------ receive message ---------\n");
	bb.flag=2;
	pthread_mutex_unlock (&bb.mutex);
}

void call_item(void *arg){
	int status;
	int status2;

	status = pthread_mutex_trylock (&bb.mutex);

	if (status != 0)
		return status;
	while(status2 == NULL && bb.flag != 0 && bb.receive_count !=0)
		status2 = pthread_cond_wait (&bb.send, &bb.mutex);

	if (status2 != 0) {
		pthread_mutex_unlock(&bb.mutex);
		return status;
	}
	
	if(bb.flag==0)
		bb.client_code = (int)arg;
	bb.flag = 1;

	if (status = pthread_cond_signal(&bb.call)) {
		pthread_mutex_unlock (&bb.mutex);
		return status;
	}

	pthread_mutex_unlock (&bb.mutex);
}

void receive_item(void *arg){
	int status;
	status = pthread_mutex_lock (&bb.mutex);
	while(status == NULL && (bb.flag != 2 || bb.flag == 0))
		status = pthread_cond_wait (&bb.receive, &bb.mutex);

	printf("Thread %d send: %s\n", bb.client_code, bb.message);
	
	bb.receive_count ++;
	if(bb.receive_count > 4){
		bb.receive_count = 0;
		bb.flag=0;
		pthread_cond_signal(&bb.send);
	}

	pthread_mutex_unlock (&bb.mutex);
	
}

main () {
	int status;
	void *result;
	int i;
	pthread_t producer_tid, consumer_tid[5];
	pthread_cond_signal(&bb.send);

	/* 쓰레드 생성 */
	status = pthread_create (&producer_tid, NULL, sender, NULL);

	if (status != 0)
		perror ("Create producer thread");
	
	for(i = 0; i < 5; i++)
		status = pthread_create (&consumer_tid[i], NULL, receiver, (int *)i);
	if (status != 0)
		perror ("Create consumer thread");
	

	status = pthread_join(producer_tid, NULL);
	if (status != 0)
		perror ("Join producer thread");
	
	for(i = 0; i < 5; i ++)
		status = pthread_join(consumer_tid[i], NULL);
	if (status != 0)
		perror ("Join consumer thread");
	
}
