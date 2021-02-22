
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main() {
    int fd[2];
    int size=0;

    if(pipe(fd)<0)
    {
        printf("ошибка");
        exit(1);
    }
    fcntl(fd[1], F_SETFL, fcntl(fd[1], F_GETFL) | O_NONBLOCK);
    while (write(fd[1], "a", 2) == 2) {
        size += 2;
    }
    printf("%d\n",size);

    return 0;
}
