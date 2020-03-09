#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#ifndef SEMQ_SIZE
#define SEMQ_SIZE 10000
#endif

typedef struct queue_t
{
	int head, tail;
	int values[SEMQ_SIZE];
	sem_t spaces, items;
	pthread_mutex_t read_lock, write_lock;
} queue_t;

queue_t *sem_queue_make(){
	queue_t *q = (queue_t*)malloc(sizeof(queue_t));
	if(q == NULL)
		return NULL;
	
	q->head = q->tail = 0;
	sem_init(&(q->spaces), 0, SEMQ_SIZE);
	sem_init(&(q->items), 0, 0);
	pthread_mutex_init(&(q->read_lock), NULL);
	pthread_mutex_init(&(q->write_lock), NULL);
	
	return q;
}

void sem_queue_free(queue_t *q){
	sem_destroy(&q->spaces);
	sem_destroy(&q->items);
	pthread_mutex_destroy(&q->read_lock);
	pthread_mutex_destroy(&q->write_lock);

	free(q);
}

void sem_queue_push(queue_t *q, int value){
	sem_wait(&q->spaces);
	pthread_mutex_lock(&q->write_lock);
	q->values[q->tail] = value;
	q->tail = (q->tail + 1) % SEMQ_SIZE;
	pthread_mutex_unlock(&q->write_lock);
	sem_post(&q->items);
}

int sem_queue_pop(queue_t *q){
	sem_wait(&q->items);
	pthread_mutex_lock(&q->read_lock);
	int val = q->values[q->head];
	q->head = (q->head + 1) % SEMQ_SIZE;
	pthread_mutex_unlock(&q->read_lock);
	sem_post(&q->spaces);
	return val;
}

/* // Test code
int main(void){
	queue_t *q = sem_queue_make();

	sem_queue_push(q, 10);

	int val = sem_queue_pop(q);
	printf("%d\n", val);

	sem_queue_free(q);

	return 0;
}
*/