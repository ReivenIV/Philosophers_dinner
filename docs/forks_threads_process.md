
# Processes, Threads, `fork()`
_Processes, Threads, and the `fork()` function in C in a simple way_

---

### What is a Process?
A process is like a running program on your computer. When you run a C program, the operating system (like Windows or Linux) creates a process for it. Each process has its own memory space, so it’s separate from other processes. Think of it as a little worker doing its job independently.

- **Example**: If you open a web browser and a music player, those are two separate processes. They don’t share memory or mess with each other.

In C, a process starts when you run your program, and it keeps going until the program ends.

---

### What is a Thread?
A thread is like a smaller worker *inside* a process. A process can have multiple threads, and they all share the same memory space. Threads are great for doing multiple things at once within the same program, like splitting tasks.

- **Example**: Imagine a process is a kitchen. The kitchen (process) can have multiple cooks (threads) working together, sharing the same ingredients (memory). They cooperate but do different tasks, like chopping vegetables or boiling water.

Threads are lighter and faster to create than processes because they don’t need their own separate memory.

---

### What is `fork()`?
In C, `fork()` is a function (mostly used on Linux/Unix systems) that creates a new process. It’s like cloning the current process. When you call `fork()`, you get two processes:
1. The **parent process** (the original one).
2. The **child process** (the new copy).

Both processes are almost identical at first, but they can do different things after the `fork()`. The `fork()` function returns:
- **0** to the child process.
- A positive number (the child’s process ID) to the parent process.
- A negative number if something goes wrong.

Think of `fork()` as splitting one worker into two workers who can now do separate jobs.

---

### Simple Example of `fork()`
Let’s write a small C program to see `fork()` in action. This example will show how the parent and child processes work.

```c
#include <stdio.h>
#include <unistd.h> // Needed for fork()
#include <sys/types.h> // Needed for pid_t

int main() {
	pid_t pid;																	// This is a variable to store the process ID

	// Call fork() to create a new process
	pid = fork();

	if (pid < 0) { 																// If fork() fails
		printf("Error: Fork failed!\n");
	}
	else if (pid == 0) {														// This code runs in the child process
		printf("Hello, I am the child process! My PID is %d\n", getpid());
	}
	else {																		// This code runs in the parent process
		printf("Hello, I am the parent process! My child's PID is %d\n", pid);
	}

	return 0;
}
```

#### How to Run It:
1. Save this code in a file called `fork_example.c`.
2. Open a terminal (on Linux or a Unix-like system).
3. Compile it with: `gcc fork_example.c -o fork_example`.
4. Run it with: `./fork_example`.

#### What Happens:
- The program starts as one process (the parent).
- When `fork()` is called, it creates a child process.
- The parent and child both print a message.
- You might see output like:
  ```
  Hello, I am the parent process! My child's PID is 1234
  Hello, I am the child process! My PID is 1234
  ```
  (The order of the lines might vary because both processes run at the same time.)

Here:
- `getpid()` gives the process ID of the current process.
- The parent gets the child’s PID from `fork()`.

---

### Processes vs. Threads: Key Differences
- **Processes**: Separate memory, heavier to create, don’t share data easily. Use `fork()` to make them.
- **Threads**: Share memory, lighter to create, good for teamwork inside one program. You’d use libraries like `pthread` in C to create threads (not `fork()`).

---

### Simple Thread Example (Bonus)
Here’s a basic example using threads with the `pthread` library in C. This shows two threads running in the same process.

```c
#include <stdio.h>
#include <pthread.h>

// This is the function each thread will run
void* say_hello(void* arg) {
	printf("Hello from a thread!\n");
	return NULL;
}

int main() {
	pthread_t thread1, thread2;								// Variables to hold thread IDs

	// Create two threads
	pthread_create(&thread1, NULL, say_hello, NULL);
	pthread_create(&thread2, NULL, say_hello, NULL);

	// Wait for threads to finish
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Main program done!\n");
	return 0;
}
```

#### How to Run It:
1. Save as `thread_example.c`.
2. Compile with: `gcc thread_example.c -o thread_example -lpthread`.
3. Run with: `./thread_example`.

#### Output:
```
Hello from a thread!
Hello from a thread!
Main program done!
```
(The order of "Hello" messages might vary.)

---

### Summary
- **Process**: A full program running on its own. Use `fork()` to make a new one.
- **Thread**: A smaller task inside a process. Use `pthread` to create them.
- **`fork()`**: Splits a process into two (parent and child).
