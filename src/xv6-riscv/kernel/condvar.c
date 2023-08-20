#include "condvar.h"
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "stat.h"
#include "proc.h"

void cond_wait(struct cond_t *cv, struct sleeplock *lk){
    acquiresleep(lk);
    while(cv->value == 1) condsleep(cv, lk);
    releasesleep(lk);
}

void cond_signal(struct cond_t *cv){
    wakeupone(cv);
}

void cond_broadcast(struct cond_t *cv){
    wakeup(cv);
}