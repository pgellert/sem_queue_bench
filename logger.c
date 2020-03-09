#include <stdio.h>
#include <stdlib.h>

void log_result(int sem_q_size, int produce_size, int num_of_iters, double seq_time, double threaded_time){
	printf("Time seq: %.3fms\n", seq_time);
	printf("Time threaded: %.3fms\n", threaded_time);

	FILE *log;
	log = fopen("data.csv", "a");

	if(log == NULL)
	{
		printf("Error opening file...");
		exit(1);
	}

	fprintf(log, "%d,%d,%d,%.3f,%.3f\n", sem_q_size, produce_size, num_of_iters, seq_time, threaded_time);

	fclose(log);
}