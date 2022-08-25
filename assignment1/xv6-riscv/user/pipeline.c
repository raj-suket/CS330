#include <kernel/types.h>
#include <user/user.h>

void create_n_processes(int n, int fd[2]){
    int x;
    if(n == 1){
        read(fd[0], &x, 1);
        x = x + getpid();
        printf("%d : %d\n", getpid(), x);
        write(fd[1], &x, 1);
        return;
    }

    int rv = fork();
    if(rv == 0){
        // entered the child
        
        // recursively call the process to generate 1 less child;
        create_n_processes(n-1, fd);
    }else{
        // wait for the child process to finish
        wait(0);
        read(fd[0], &x, 1);
        x = x + getpid();
        printf("%d : %d\n", getpid(), x);
        write(fd[1], &x, 1);
    }
    return;
}

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
    
    create_n_processes(n, fd);

    exit(0);
}