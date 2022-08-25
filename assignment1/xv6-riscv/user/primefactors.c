#include <kernel/types.h>
#include <user/user.h>

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};


int get_largest_divisible_prime(int n){
    for(int i = 24; i >= 0; i--){
        if(n % primes[i] == 0) return primes[i];
    }
    return -1;
}

void solve(int fd[2]){
    int n;
    read(fd[0], &n, 1);

    if(n == 1) return;

    int p = get_largest_divisible_prime(n);
    int count = 0;
    while(n % p == 0){
        n /= p;
        count++;
    }

    int rv = fork();

    if(rv == 0){
        // entered a child process;
        write(fd[1], &n, 1);
        solve(fd);
    }else{
        wait(0);
        while(count--){
            printf("%d, ", p);
        }
        printf("[%d]\n", getpid());
    }
    return;
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
    
    solve(fd);

    exit(0);
}
