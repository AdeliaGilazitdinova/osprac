/*
 При многократном запуске программы идентификатор процесса – PID и идентификатор родительского процесса – PPID были разными (функции getpid() и getppid() с каждыйм запуском возвращали разные значение), так как c каждым запуском порождается новый процесс и соотвенно ему присваевается новый идентификатор
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, const char * argv[]) {
    printf("pid = %d\nppid = %d\n", (int)getpid(), (int)getppid());
    return 0;
}
