#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if(argc > 1){
        printf("Warning: No argument expected with uptime\n");
    }
    printf("%d seconds %d milliseconds\n", (uptime()/10), ((uptime()%10)*100));
    exit(0);
}