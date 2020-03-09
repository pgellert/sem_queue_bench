CC=gcc -fsanitize=address,undefined -Wno-deprecated

compile:
	#$(CC) -o measure measure.c
	#$(CC) -o sem_queue sem_queue.c
	$(CC) -o bench bench.c

test:
	#./measure
	#./sem_queue
	./bench

run: compile test

.PHONY: clean
clean:
	rm measure#