### **What is POSIX?**  
POSIX (**Portable Operating System Interface**) is a **set of rules** that makes programs work the same way on **different operating systems** (like Linux, macOS, etc.). It helps software developers write code that can run on many systems without changes.  

### **What is pthread?**  
`pthread` (**POSIX threads**) is a **library** in C that allows programs to create and manage **multiple threads**. Threads help a program do multiple things at once, making it faster.  

### **Example of pthread in action:**  
Think of a restaurant:  
- **POSIX** is like a **rulebook** for how all restaurants should work.  
- **pthread** is like **hiring extra chefs** (threads) to prepare food faster.  


### Exemple : 
```c
#include <stdio.h>
#include <pthread.h>  // Include the pthread library
#include <unistd.h>   // For sleep()

void *my_thread(void *arg) {
    printf("Hello from the thread!\n");
    sleep(1);// Pause for 1 second
    printf("Thread is done!\n");
    return NULL;// End of the thread
}

int main() {
    pthread_t thread;  // Declare a thread variable

    pthread_create(&thread, NULL, my_thread, NULL);      // Create a new thread that runs the function 'my_thread'
    printf("Hello from the main program!\n");

    pthread_join(thread, NULL);                         // Wait for the thread to finish
    printf("Main program is done!\n");
    return 0;
}
```
