// src : https://medium.com/@jalal92/lets-discuss-threads-grab-a-coffee-ad4d4ebf7181
// MUTEX = "mutual exclusive"

/*
 * A Mutex, short for MUTual-EXclusion, acts like a lock 🔒. 
 * It ensures that only one thread (waiter) can access the critical section 
 * (our register, the code that leads to the race condition) 
 * at a time.

 * Flipping a coin or throwing a dice produce a “mutual exclusive” behaviour.

 * In few words : ""MUTEX is to ensure that the workers/threads are not overlaping each other acessing data""
	ensures that multiple threads (or workers) do not overlap each 
	other when accessing shared resources. This prevents race conditions,
	where the outcome of operations depends on the unpredictable timing of threads.
*/
#include <stdio.h>
#include <pthread.h>

#define RACE_CONDITION 100000
int             g_drinks_served;
// Global mutex for synchronizing access to g_drinks_served
// This is a struct, think about a 🔒 that can be closed or open.
pthread_mutex_t mutex; 


void *serve_drink(void *arg)
{
 int i;
 i = 0;
 while (i++ < RACE_CONDITION)
		{
		// Locking the mutex before updating the global variable
		// before the waiter didn't do its stuff, nobody writes here
		// 🔒 closing the MUTEX
				pthread_mutex_lock(&mutex); 
		/*
		 🚨 critical section 🚨
			"scheduler just leave me do my job here"
					1)LOAD    <-
					2)ADD     <-
					3)STORE   <-
		*/
			g_drinks_served++;
		
		// 🔓 opening MUTEX
			pthread_mutex_unlock(&mutex); 
		}
 return (NULL);
}
int main(void)
{
		pthread_t waiter1;
		pthread_t waiter2;
		// Initialize the mutex
		// setting the value to open 🔓 for example
		if(pthread_mutex_init(&mutex, NULL) != 0)
		{
			printf("Mutex initialization failed!\n");
			return 1;
		}
		pthread_create(&waiter1, NULL, serve_drink, NULL);
		pthread_create(&waiter2, NULL, serve_drink, NULL);
		
		pthread_join(waiter1, NULL);
		pthread_join(waiter2, NULL);

		pthread_mutex_destroy(&mutex);                         //avoid leaks by destroying the struct mutex
		printf("Total drinks served: %d\\n", g_drinks_served);
		return (0);
}