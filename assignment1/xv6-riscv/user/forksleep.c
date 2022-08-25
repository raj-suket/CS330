#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char * argv[]){
    if(argc != 3){
        printf("Expected two arguments with forksleep\n");
    }else{
        int m= atoi(argv[1]);
        int n= atoi(argv[2]);
        
        if(!(n==0 || n==1)){
            printf("Second argument must be 0 or 1\n");
        }else{
            int rc = fork();

            if(rc < 0){
                printf("Some error occured\n");
            }else if(n==0){
                if(rc==0){
                    sleep(m);
                    printf("pid child: %d\n",getpid());
                }else{
                    printf("pid parent: %d\n",getpid());
                }
            }else{
                if(rc>0){
                    sleep(m);
                    printf("pid parent: %d\n",getpid());
                }else{
                    printf("pid child: %d\n",getpid());
                }
            }
            wait(0);
        }
    }
    exit(0);
}