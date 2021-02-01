#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, const char * argv[]) {
    pid_t pid = fork();
    if(pid == -1){
        printf("error");
    } else if (pid == 0){
        printf("pid = %d (child)\n", (int)getpid());
    } else {
        printf("ppid = %d (parent)\n", (int)getppid());
    }
    return 0;
}
