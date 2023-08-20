// #include "semaphore.h"
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
// #include "sleeplock.h"
// #include "file.h"
#include "stat.h"
#include "proc.h"
#include "barrier.h"    

void sem_init(struct semaphore * s, int x){
    acquiresleep(&(s->lk));
    s->x = x;
    releasesleep(&(s->lk));
}

void sem_wait(struct semaphore * s){
    acquiresleep(&(s->lk));
    s->x -= 1;
    if(s->x < 0){
        sleepsemaphore(s, &(s->lk));
    }
    releasesleep(&(s->lk));
}

void sem_post(struct semaphore * s){
    
    acquiresleep(&(s->lk));
    s->x += 1;
    releasesleep(&(s->lk));
    
    wakeupsemaphore(s);
    // wakeupone process waiting cus of semaphore
}