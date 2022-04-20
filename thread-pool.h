#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#define DEFAULT_POOL_SIZE 10
#define DEFAULT_QUEUE_SIZE 512
#define DEFAULT_THREAD_TIMEOUT_MS 1
#define DEFAULT_THREAD_TIMEOUT_NS 0

// A task to complete.
typedef struct Task{
    // The argument for the task function.
    void *data;
    // The task function.
    void (*f)(void *);
}Task;

// Create a thread pool.
pthread_t *create_pool(int, int);

// Create a task.
Task *create_task(void *, void (*f)(void *));

// Destroy the pool and clean up resources.
void destroy_pool(pthread_t *, int);

// Stalls until task queue is completed.
void wait_tasks();

// Push a task into the task queue.
void push_task(Task *);

// User implemented: Frees the task data if needed.
void destroy_task_data(void *);

#endif
