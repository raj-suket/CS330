#include "sleeplock.h"

struct semaphore{
    int x;
    struct sleeplock lk;
};