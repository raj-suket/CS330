#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char * argv[]){
    printf("%d\n", getpid());
    int x=fork();
    int y=1;
    int z=2;
    if(x==0){
        printf("In child: virtual addr: %p    physical addr: %ld\n",&y,getpa(&y));
        sleep(1);
        printf("z.In child: virtual addr: %p    physical addr: %ld\n",&z,getpa(&z));
        // printf("in child, ppid=%d\n", getppid());
        // printf("in child, pid=%d\n",getpid());
    }else{
        wait(0);
        // yield();
        printf("In parent: virtual addr: %p     physical addr: %ld\n",&y,getpa(&y));
        printf("z.In parent: virtual addr: %p    physical addr: %ld\n",&z,getpa(&z));
        // printf("in parent, pid=%d\n\n", getpid());
    }
    exit(0);
}