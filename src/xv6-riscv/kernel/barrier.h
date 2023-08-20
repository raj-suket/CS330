#include "condvar.h"
#include "semaphore.h"

struct barrier{
    int flag;
    int left_processes;
    int num_processes;
    int instance; 
    struct cond_t cv;
    struct sleeplock lk;
};

struct bounded_buffer_semaphore {
    int size;
    struct semaphore empty;
    struct semaphore full;
    struct semaphore prod;
    struct semaphore cons;

    int buffer[20];
    int nextp;
    int nextc;
};

struct buffer_elem{
    int x;
    int full;
    struct sleeplock lock;
    struct cond_t inserted;
    struct cond_t deleted;
};

struct bounded_buffer_condition{
    struct buffer_elem buffer[20];
    int tail;
    int head;
    
    struct sleeplock lock_delete;
    struct sleeplock lock_insert;
    struct sleeplock lock_print;
};

extern struct bounded_buffer_condition buffer_condition;

extern struct bounded_buffer_semaphore buffer_sem;

extern struct barrier barrier_array[10];