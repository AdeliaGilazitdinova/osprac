#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
    pid_t pid = fork();
    if(pid == -1){
        printf("error");
    } else if (pid == 0){
        printf("pid = %d (child)\n", (int)getpid());
        (void)execle("/bin/echo", "/bin/echo", "Hello,", "world!", 0, envp);
    } else {
        printf("pid = %d (parent)\n", (int)getpid());
    }
    
    return 0;
}
