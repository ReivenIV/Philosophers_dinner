// Hi dear, exemple src: https://medium.com/@jalal92/lets-discuss-threads-grab-a-coffee-ad4d4ebf7181

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int x = 42;
int main()
{
    pid_t pid = fork(); 												// Creates a new process
 
    if (0 == pid)  														// child
    {
        x++;
        printf("Child process: Value of x = %d\n", x);
    }
    else  																//parent
    {
        wait(NULL); 													// Wait for child to finish
        printf("Parent process: Value of x = %d\n", x);
    }
}