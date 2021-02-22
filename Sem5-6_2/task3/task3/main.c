
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd[2];
    int size=0;
    
    if(pipe(fd)<0)
    {
        printf("ошибка");
        exit(1);
    }
    else
    {
        
        while (write(fd[1], "a", 2) == 2) {
            size += 2;
            printf("%d\n", size);
        }
    }
    
    return 0;
}
