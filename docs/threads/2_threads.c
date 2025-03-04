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
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *make_coffee(void *arg)
{
 printf("Making coffee...\n");
 sleep(1);
 printf("++ Coffee ready!\n");
 return (NULL);
}

void *make_pastry(void *arg)
{
 printf("Baking pastry...\n");
 sleep(2);
 printf("++ Pastry ready!\n");
 return (NULL);
}

int main(void)
{
 pthread_t coffee_thread;
 pthread_t pastry_thread;

 pthread_create(&coffee_thread, NULL, make_coffee, NULL);
 pthread_create(&pastry_thread, NULL, make_pastry, NULL);
 
 //Before handing the order to customer, i nees to WAIT both threads
 pthread_join(coffee_thread, NULL);
 pthread_join(pastry_thread, NULL);
 
 sleep(1);
 printf("\n\n\tHere is your comand. \n\tThx for coming to Starbucks!\n"
	 "\there's the ☕️ 'n 🥐\n\n\n");
 return (0);
}

/*

Some explanations : 
`pthread_join()` **makes the main program wait** for a thread to finish before continuing.  

### **Why is it needed?**  
In the code, you **must** wait for both the `coffee_thread` and `pastry_thread` to finish **before giving the order to the customer**.  

### **How does it work?**  
When you call:  
```c
pthread_join(coffee_thread, NULL);
pthread_join(pastry_thread, NULL);
```
- The main program **pauses** until `make_coffee()` is done.  
- Then, it **pauses again** until `make_pastry()` is done.  
- After both are ready, it prints:  
  ```
	  Thx for coming to Starbucks!
	  here's the ☕️ 'n 🥐
  ```

### **Without pthread_join?**  
If you remove `pthread_join()`, the main program might finish **before** the coffee or pastry is ready! The program could exit early, stopping the threads.

### **Example Summary**  
- `pthread_create()`: Starts a new thread.  
- `pthread_join()`: **Waits** for a thread to finish before moving on.  

*/