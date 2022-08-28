#include <kernel/types.h>
#include <user/user.h>

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};


int get_smallest_divisible_prime(int n){
    for(int i = 0; i <= 24; i++){
        if(n % primes[i] == 0) return primes[i];
    }
    return -1;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Program expects 1 arguement, %d found", (argc - 1));
        exit(1);
    }
    int n = atoi(argv[1]);
    if(n <= 0){
        printf("The value of n should be a positive integer");
        exit(2);
    }

    
    int fd[2];
    pipe(fd);
    // we will use this pipe to store the number to transfer the end-result number

    write(fd[1], &n, 1);

    while(1){
        read(fd[0], &n, 1);
        if(n == 1) exit(0);

        int p = get_smallest_divisible_prime(n);
        int count = 0;
        while(n % p == 0){
            n /= p;
            count++;
        }

        while(count--){
            printf("%d, ", p);
        }
        printf("[%d]\n", getpid());

        int rv = fork();
        if(rv == 0){
            write(fd[1], &n, 1);
        }else{
            wait(0);
            exit(0);
        }
    }
}