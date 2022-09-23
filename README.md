# Philosophers

*These philosophers killed me before they died.* 🙂

## The rules of the philosopher project:

The dining philosophers problem is a computer puzzle that introduces us to the concurrent programming. The problem illustrates synchronization issues. Our philosophers project describes a version of this problem.

## The Mandatory Part

### The Rules:

(see *en.subject.pdf*)

### Concurrent Programming

*because being concurrent is different from being parallel*

The idea lies behind concurrency is to perform multiple tasks within a program simultaneously, most of today's programs are concurrent.Without concurrency you can't listen to *spotify* while editing your code on *VS code*. Amazing ha! but believe me there are alot of issues come from this we will see them later on.
Multiple tasks executed at the same time can mean that these tasks being run in parallel, but this is not true. The difference between concurrency and parallisme is that the latter run tasks simultaneously while concurrency depends on *task scheduler* that switches between the tasks very quickly and perform each task in a small amount of time so we can't notice the switching and appear like parallel.
we can implement concurrent programming using Threads or Processes.

### What is a Thread?

a thread is a small set of instructions or tasks. a Thread is initiated by a process, every process has at least one thread, *main thread*.Threads cannot be shared among processes.
All the threads have the same **Process Id**. Moreover all threads inherited their parent process attributes such as , the working directory, user ID, group ID.The threads also have access to all file descriptors opend by other threads within the same process. Therefore they can manipulate files pointed by these file descriptors. All threads share the same memory space of the owner process (which can cause problems)

### Manipulate Threads

The `<pthread.h>` library provides us with alot of useful functions to manipulate threads.
we compile and link this library using : `gcc file.c -pthread`

#### Create Threads

we can create a new thread from any other thread by using the pthread_create() function:

`int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);`

- **thread** : a pointer to *pthread_t* variable, used to store the ID of the thread we are creating.
- **attr** : a structure that's used at thread creation time to determine attributes for the new thread. For our philosopher project we will use NULL.
- **start_routine** : The function that determine the behavior of the newly created thread.
- **arg** : the argument we pass to the *start_routine()* function. If the function requires more than one argument we should pass a structure to it.

A successfull call to *pthread_create()* stores the id of the new thread in *thread* variable, and the function return 0,otherwise it returns error number.

#### Join Or Detach a Thread

When a thread calls join it will be blocked until the termination of the thread whose id is stored in the *thread* varibale, its prototype is :

`int pthread_join(pthread_t thread, void **retval);`

- **thread** : The id of the thread we should wiat for.
- **retval** : if it's not NULL, this variable stores the return value of *the start_routine()* function

*pthread_join()* return 0 on success, or error number on failure.

in some cases we have not to wait the termination of a scpecific thread, for that we can use the *pthread_detach()* to let the thread to release used ressources back to the system.
After detaching a Thread other threads can't wait for it using *pthread_join()*.Its prototype is :

`int pthread_detach(pthread_t thread);`

### Managing Thread's Shared memory:

As we stated before the threads share the same process's memory. Each thread of course has its own stack memory but other threads within the same process have pointer to that memory wich make the access easy which can cause synchronization errors.

#### Data races
a Data race is a situation where multiple threads try to access the same memory region at the same time and modify it. So in order to solve this issue we use Mutexes.

#### Mutexes

Mutexes are simply variables or objects which are used to synchronize the access of a shared ressource. To understand better mutexes let's imagine this scenario:

Let's go back by time when there are no cell phones, so the only way for people to communicate at that time is by using street phones. This phone exist in a room which can fit to one person at the time and locked from the inside (privacy matter). and there is a long line of people waiting their turn to use it. Once a person leave the phone room the next one can enter an use the phone and so on.

The phone room called a critical section, The phone is the shared ressource and the people are the threads that attempt to use the shared ressource within the critical section
and the lock of the room is the *mutex*. So basically a mutex is a lock we used it to protect our program from data races.

**Using mutexes**

Before using a mutex we should initialize it with *pthread_mutex_init()*, its prototype is:

`int	pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);`

- **mutex** : a pointer to a variable of *pthread_mutex_t* type.
- **mutexattr** : a pointer to specific attributes of the mutex.

this function returns 0 on success, Otherwise it returns a non-0 value.

Now we can use our mutex to protect the shared memory.

`int	pthread_mutex_lock(pthread_mutex_t *mutex);`

`int	pthread_mutex_unlock(pthread_mutex_t *mutex);`

- **mutex** : a pointer to the variable we want to use for lock.

if the mutex is unlocked, the *pthread_mutex_lock()* function locks it and the thread invoked the function become its owner.Otherwise If it's already locked the calling thread suspends its execution until this mutex is unlocked again.

The *pthread_mutex_unlock()* Try to unlock a mutex. This function does not check if a mutex is already locked.

When done using mutexes we should destroy them by calling the *pthread_mutex_destroy()*. This function takes the pointer to that mutex as argument and free its ressources. Note that the mutex should be unlocked. Its prototype is:

`int	pthread_mutex_destroy(pthread_mutex_t *mutex);`


