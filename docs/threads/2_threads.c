#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/*

`sleep()` makes the program **pause** for a few seconds.  

For example:  
```c
sleep(2);  // Wait for 2 seconds
```
During this time, the program **does nothing** and just waits.  
Useful when testing threads or adding delays.

*/
void *task1(void *arg) {
    printf("Task 1: Counting...\n");
    sleep(1);
    printf("Task 1 done!\n");
    return NULL;
}

void *task2(void *arg) {
    printf("Task 2: Printing a message...\n");
    sleep(2);
    printf("Task 2 done!\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, task1, NULL);
    pthread_create(&thread2, NULL, task2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both tasks finished!\n");

    return 0;
}
