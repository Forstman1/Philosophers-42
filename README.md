# Philosophers-42

The Dining Philosopher Problem – The Dining Philosopher Problem states that K philosophers seated around a circular table with one chopstick between each pair of philosophers. There is one chopstick between each philosopher. A philosopher may eat if he can pick up the two chopsticks adjacent to him. One chopstick may be picked up by any one of its adjacent followers but not both. 


![Dinning problem](https://media.geeksforgeeks.org/wp-content/uploads/dining_philosopher_problem.png)

## What is a Thread?
A thread is a single sequence stream within in a process. Because threads have some of the properties of processes, they are sometimes called lightweight processes.

## What are the differences between process and thread?
Threads are not independent of one other like processes as a result threads shares with other threads their code section, data section and OS resources like open files and signals. But, like process, a thread has its own program counter (PC), a register set, and a stack space.

## Why Multithreading?
Threads are popular way to improve application through parallelism. For example, in a browser, multiple tabs can be different threads. MS word uses multiple threads, one thread to format the text, other thread to process inputs, etc.
Threads operate faster than processes due to following reasons:
1) Thread creation is much faster.
2) Context switching between threads is much faster.
3) Threads can be terminated easily
4) Communication between threads is faster.

### There are three states of the philosopher: 

* THINKING 
* HUNGRY
* EATING

 Here there are two semaphores: Mutex and a semaphore array for the philosophers. Mutex is used such that no two philosophers may access the pickup or putdown at the same time. The array is used to control the behavior of each philosopher. But, semaphores can result in deadlock due to programming errors.
 
 
 Dining Philosophers Problem
 
 
 - Let's understand the Dining Philosophers Problem with the below code, we have used fig 1 as a reference to make you understand the problem exactly. The five Philosophers are represented as P0, P1, P2, P3, and P4 and five chopsticks by C0, C1, C2, C3, and C4.

![Dinning problem](https://static.javatpoint.com/operating-system/images/os-dining-philosophers-problem2.png)

```
Void Philosopher  
 {  
 while(1)  
  {  
   take_chopstick[i];  
   take_chopstick[ (i+1) % 5] ;  
   . .  
   . EATING THE NOODLE  
   .  
   put_chopstick[i] );  
   put_chopstick[ (i+1) % 5] ;  
   .  
   . THINKING  
  }  
```


Suppose Philosopher P0 wants to eat, it will enter in Philosopher() function, and execute take_chopstick[i]; by doing this it holds C0 chopstick after that it execute take_chopstick[ (i+1) % 5]; by doing this it holds C1 chopstick( since i =0, therefore (0 + 1) % 5 = 1)

Similarly suppose now Philosopher P1 wants to eat, it will enter in Philosopher() function, and execute take_chopstick[i]; by doing this it holds C1 chopstick after that it execute take_chopstick[ (i+1) % 5]; by doing this it holds C2 chopstick( since i =1, therefore (1 + 1) % 5 = 2)

But Practically Chopstick C1 is not available as it has already been taken by philosopher P0, hence the above code generates problems and produces race condition.

The solution of the Dining Philosophers Problem
We use a semaphore to represent a chopstick and this truly acts as a solution of the Dining Philosophers Problem. Wait and Signal operations will be used for the solution of the Dining Philosophers Problem, for picking a chopstick wait operation can be executed while for releasing a chopstick signal semaphore can be executed.
