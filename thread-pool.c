#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <semaphore.h>

#include "thread-pool.h"
#include "linked-list.h"

LinkedList *g_taskQ;
sem_t g_taskP, g_taskC;
pthread_mutex_t g_queueLock;
int g_killthreads = 0;

// Checks if a pointer is null and throws exception if it is.
void _nullCheck(void *ptr){
    if(ptr == NULL){
        fprintf(stderr, "Null reference exception");
        exit(1);
    }
}

// Pops a task off the top of the queue under mutex lock.
LLNode *_pop_task(){
    pthread_mutex_lock(&g_queueLock);
    LLNode *node = g_taskQ -> head;
    remove_node(g_taskQ, node);
    pthread_mutex_unlock(&g_queueLock);
    return node;
}

// Runs each thread in the pool.
void *_run_thread(void *arg){
    struct timespec timeout = { DEFAULT_THREAD_TIMEOUT_MS, DEFAULT_THREAD_TIMEOUT_NS };
    while(!g_killthreads){
        int res = sem_timedwait(&g_taskP, &timeout);
        if(res == -1 && errno == ETIMEDOUT){
            continue;
        }

        LLNode *node = _pop_task();
        Task *task = (struct Task *)node -> value;
        task -> f(task -> data);
        destroy_node(node);
        sem_post(&g_taskC);
    }
    return NULL;
}

void destroy_node_value(void * value){
    Task *task = (Task *)value;
    destroy_task_data(task -> data);
    free(task);
}

pthread_t *create_pool(int poolSize, int queueSize){
    sem_init(&g_taskP, 0, 0);
    sem_init(&g_taskC, 0, queueSize);
    pthread_mutex_init(&g_queueLock, NULL);
    g_taskQ = create_list();

    pthread_t *pool = malloc(sizeof(pthread_t) * poolSize);
    nullCheck(pool);
    for(int i = 0; i < poolSize; i++){
        pthread_create(&pool[i], NULL, &_run_thread, NULL);
    }
    return pool;
}

Task *create_task(void * data, void (*f)(void *)){
    Task *task = malloc(sizeof(Task));
    nullCheck(task);
    *task = (Task){
        .data = data,
        .f = f
    };
    return task;
}

void destroy_pool(pthread_t *pool, int size){
    g_killthreads = 1;
    for(int i = 0; i < size; i++){
        pthread_join(pool[i], NULL);
    }
    destroy_list(g_taskQ);
    free(pool);
    sem_destroy(&g_taskP);
    sem_destroy(&g_taskC);
    pthread_mutex_destroy(&g_queueLock);
}

void wait_tasks(){
    while(g_taskQ -> size > 0){}
}

void push_task(Task *task){
    sem_wait(&g_taskC);
    LLNode *node = create_node(task);
    append_node(g_taskQ, node);
    sem_post(&g_taskP);
}
