#include "kernel/types.h"
#include "user/user.h"

int fdn[2];
int fdx[2];

void rec(){
    int n, x;
    
    read(fdn[0], &n, sizeof(int));
    // close(fdn[0]);
    
    if(n==0){
        close(fdn[0]);
        close(fdn[1]);
        close(fdx[0]);
        close(fdx[1]);
        return;
    }
    n--;
    
    write(fdn[1], &n, sizeof(int));
    // close(fdn[1]);
    
    read(fdx[0], &x, sizeof(int));
    // close(fdx[0]);
    
    int pid=getpid();
    x+=pid;
    printf("%d: %d\n", pid, x);
    
    write(fdx[1], &x, sizeof(int));
    // close(fdx[1]);
    
    if(fork()==0){
        // close(fdn[0]);
        // close(fdn[1]);
        // close(fdx[0]);
        // close(fdx[1]);
        rec();
    }else{
        wait(0);
    }
}

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("PLease provide 2 arguments n and x.\n");
    }else{
        int n=atoi(argv[1]);
        int x=atoi(argv[2]);
        if(n<=0){
            printf("Please provide a valid n (n must be a positive integer).\n");
        }else{
            pipe(fdn);
            // close(fdn[0]);

            pipe(fdx);
            // close(fdx[0]);
            
            write(fdn[1], &n, sizeof(int));
            // close(fdn[1]);
            
            write(fdx[1], &x, sizeof(int));
            // close(fdx[1]);
            
            rec();
        }
    }
    exit(0);
}