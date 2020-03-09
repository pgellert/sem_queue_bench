#include <stdio.h>
#include <stdlib.h>
#include "sem_queue.c"
#include "measure.c"
#include "logger.c"

#define PRODUCE_N 10000
#define SEMQ_SIZE 10000

void sem_consumer(queue_t *q){
	long long sum = 0;
	for(int i = 0; i < PRODUCE_N; i++){
		sum += sem_queue_pop(q);
	}
}

void sem_consumer10x(queue_t *q){
	for (int i = 0; i < 3; ++i)
		sem_consumer(q);
}

void sem_producer(queue_t *q){
	for(int i = 0; i < PRODUCE_N; i++){
		sem_queue_push(q, i);
	}
}

void sem_producer10x(queue_t *q){
	for (int i = 0; i < 3; ++i)
		sem_producer(q);
}



void run(){
	queue_t *q = sem_queue_make();
	
	for (int i = 0; i < 10; ++i)
	{
		sem_producer(q);
		sem_consumer(q);
	}

	sem_queue_free(q);
}

void run_threaded(){
	queue_t *q = sem_queue_make();

	pthread_t thread_id[2];

	pthread_create(&thread_id[0], NULL, sem_producer10x, q);
	pthread_create(&thread_id[1], NULL, sem_consumer10x, q);
    
    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

	sem_queue_free(q);
}



int main(void)
{
	double time_seq = measure(run);
	double time_conc = measure(run_threaded);

	log_result(SEMQ_SIZE, PRODUCE_N, 10, time_seq, time_conc);

	return 0;
}