#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>
int main(){
    int i = 0;
    // char * argv[1];
    // argv[0] = "ppid.o";
    int a = fork();
    wait(0);
    int b = fork();
    wait(0);
    int c = fork();
    wait(0);
    if(a | b | c) {
        while(1){
            if(i > 10) exit(0);
            printf("[%d] : %d\n",getpid(), i++);
        }
    }
    else{
        printf("HI\n");
        printf("%d\n", getpid());
        int x=fork();
        // int y;
        // int z;
        if(x==0){
            // printf("In child: virtual addr: %p    physical addr: %p\n",&y,getpa(&y));

            // printf("z.In child: virtual addr: %p    physical addr: %p\n",&z,getpa(&z));
            printf("in child, ppid=%d\n", getppid());
            printf("in child, pid=%d\n",getpid());
        }else{
            // wait(0);
            yield();
            // printf("In parent: virtual addr: %p     physical addr: %p\n",&y,getpa(&y));
            // printf("z.In child: virtual addr: %p    physical addr: %p\n",&z,getpa(&z));
            printf("in parent, pid=%d\n\n", getpid());
        }
        
        printf("BYE\n");
        exit(0);
    }
    return 0;
}

/*
#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>
int main(){
    int i = 0;
    int a = fork();
    wait(0);
    int b = fork();
    wait(0);
    int c = fork();
    wait(0);
    if(a | b | c) while(1){
        if(i > 10) exit(0);
        printf("[%d] : %d\n",getpid(), i++);
    }
    else{
        printf("HI\n");
        exec("ppid.o", NULL);
    } 
    return 0;
}
*/