#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
int main()
{
    int     fd;
    size_t  size;
    char    resstring[14], string[] = "Hello, world!";
    (void)umask(0);
    
    if ((fd = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
    size = write(fd, string, 14);
    if (size != 14) {
        printf("Can\'t write all string\n");
        exit(-1);
    }
    if (close(fd) < 0) {
        printf("Can\'t close file\n");
    }
    
    if ((fd = open("myfile", O_RDONLY)) < 0) {
        printf("Can\'t open file\n");
        exit(-1);
    }
   
    size = read(fd, resstring, 14);
    if (size != 14) {
        printf("Can\'t read all string\n");
        exit(-1);
    }
    printf("%s\n", resstring);
    if (close(fd) < 0) {
        printf("Can\'t close file\n");
    }
    return 0;
}
