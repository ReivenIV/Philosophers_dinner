#include <stdio.h>
#include <unistd.h>		// Needed for fork()
#include <sys/types.h>	// Needed for pid_t

int main() {
	pid_t pid;																	// This is a variable to store the process ID

	// Call fork() to create a new process
	pid = fork();

	if (pid < 0) {																// If fork() fails
		printf("Error: Fork failed!\n");
	}
	else if (pid == 0) { 														// This code runs in the child process
		printf("Hello, I am the child process! My PID is %d\n", getpid());
	}
	else {																		// This code runs in the parent process
		printf("Hello, I am the parent process! My child's PID is %d\n", pid);
	}

	return 0;
}