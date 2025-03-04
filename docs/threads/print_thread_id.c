#include <stdio.h>
#include <pthread.h>

void *print_thread_id(void *tid) 
{
	printf("Thread ID: %lu\n", *(pthread_t *)tid);
	return NULL;
}

int main() {
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, print_thread_id, &thread1);
	pthread_create(&thread2, NULL, print_thread_id, &thread2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

}

/*
will output: 
Thread ID: 129181157418688
Thread ID: 129181165811392
*/