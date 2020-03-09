#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double measure(void (*f)(void)){
	clock_t t = clock(); 
	(*f)(); 
	t = clock() - t; 
	return ((double)t)/(CLOCKS_PER_SEC/1000); // in microseconds 
}


/* // Test code

void test_fun(){
	printf("Starting...\n");
	printf("This function just prints something\n");
	printf("Done!\n");
}

int main(void){
	double time_elapsed = measure(test_fun);
	printf("Time elapsed: %.3fms\n", time_elapsed); 
}
*/