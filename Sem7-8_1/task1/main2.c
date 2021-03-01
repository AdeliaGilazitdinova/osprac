#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
int main()
{
    char     *array;
    int     shmid;
    char    pathname[] = "main.c";
    key_t   key;
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if ((shmid = shmget(key, 14*sizeof(char), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
            if ((shmid = shmget(key, 14*sizeof(char), 0)) < 0) {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }
    if ((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    printf("%s\n",array);
    
    if(shmctl(shmid, IPC_RMID, NULL) < 0){
        printf("Can't free shared memory\n");
        exit(-1);
    }
    return 0;
}
