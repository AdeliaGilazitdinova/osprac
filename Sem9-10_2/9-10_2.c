#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/sem.h>

/**
 Изначальное значение семафора = 2
 Родитель отнимает 1 (D(1)), далее если это первое повторение, то он пишет сообщение в пайп и также отнимает 1 ((D(1)),
 если это последующте повторения, то родитель сначала считывает сообщение от ребенка, пишет ему сообщение, а затем только отнимает 1 ((D(1)).
 Ребенок все это время ждал значения 0 семафора (Z(0)). Далее ребенок сначала читает сообщение от родителя, затем пишет в пайп свое сообщение
 (родитель в это время ждет значения семафора равное 1 (D(1))), после чего увеличивает значение семафора на 2 ((A(2)).
 */

int main()
{
    int fd[2], result, semid, N;
    size_t size = 0;
    key_t key;
    struct sembuf mybuf;
    char resstring[14], pathname[] = "9-10_2.c";
    
    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }
    
    
    if ((key = ftok(pathname,0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t create semaphore set\n");
        exit(-1);
    }
    printf("Введите числ повторений: \n");
    scanf("%d", &N);
    
    mybuf.sem_num = 0;
    mybuf.sem_flg = 0;
    mybuf.sem_op  = 2;
    
    if (semop(semid, &mybuf, 1) < 0) {
        printf("Can\'t wait for condition\n");
        exit(-1);
    }
    
    
    result = fork();
    
    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {
        //parent
        // <= N, тк родитель должен в последний раз прочитать сообщение, а читает он с i > 0
        for (int i = 0; i <= N; i++)
        {
            mybuf.sem_num = 0;
            mybuf.sem_flg = 0;
            mybuf.sem_op  = -1;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
            
            //чтение сообщения от ребенка только с i > 0, тк первый пишет подитель
            if (i > 0) {
                size = read(fd[0], resstring, 14);
                if (size < 0) {
                    printf("Can\'t read string from pipe\n");
                    exit(-1);
                }
                printf("Parent exit, resstring: %s\n", resstring);
            }
            
            //запись сообщения родителя в пайп
            size = write(fd[1], "Hello, child!", 14);
            
            if (size != 14) {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }
            
            
            mybuf.sem_num = 0;
            mybuf.sem_flg = 0;
            mybuf.sem_op  = -1;
            
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
        }
        
        if (close(fd[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n"); exit(-1);
        }
    }
    else {
        //child
        for (int i = 0; i < N; ++i) {
            
            mybuf.sem_num = 0;
            mybuf.sem_flg = 0;
            mybuf.sem_op  = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
            
            //чтение собщения от родителя
            size = read(fd[0], resstring, 14);
            if (size < 0) {
                printf("Can\'t read string from pipe\n");
                exit(-1);
            }
            printf("Child exit, resstring: %s\n", resstring);
            
            //запись сообщения в пайп родителю
            size = write(fd[1], "Hello, parent", 14);
            if (size != 14) {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }
            
            mybuf.sem_num = 0;
            mybuf.sem_flg = 0;
            mybuf.sem_op  = 2;
            
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can\'t wait for condition\n");
                exit(-1);
            }
        }
        
        
        if (close(fd[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n"); exit(-1);
        }
        if (close(fd[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n"); exit(-1);
        }
    }
    return 0;
}
