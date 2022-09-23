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

#### Create Threads

we can create a new thread from any other thread by using the pthread_create() function:
`int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);`

- **thread** : a pointer to *pthread_t* variable, used to store the ID of the thread we are creating.
- **attr** : a structure that's used at thread creation time to determine attributes for the new thread. For our philosopher project we will use NULL.
- **start_routine** : The function that determine the behavior of the newly created thread.
- **arg** : the argument we pass to the *start_routine()* function. If the function requires more than one argument we should pass a structure to it.

a successfull call to *pthread_create()* stores the id of the new thread in thread variable, and the function return 0,otherwise it returns error number.

