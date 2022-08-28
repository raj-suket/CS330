#include <kernel/types.h>
#include <user/user.h>

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Program expects 2 arguements, %d found", (argc - 1));
        exit(1);
    }
    int n = atoi(argv[1]);
    int x = atoi(argv[2]);
    if(n <= 0){
        printf("The value of n should be a positive integer");
        exit(2);
    }

    // make a filedescriptor for creating a pipe;
    int fd[2];
    pipe(fd);

    write(fd[1], &x, 1);
    
    while(1){
        
        if(n == 0){
            exit(0);
        } 

        read(fd[0], &x, sizeof(int));
        x = x + getpid();
        printf("%d : %d\n", getpid(), x);
        write(fd[1], &x, sizeof(int));
        close(fd[0]);
        close(fd[1]);

        int rv = fork();
    
        if(rv == 0){
            n--;
        }else{
            wait(0);
            exit(0);
        }
    }

    exit(0);
}