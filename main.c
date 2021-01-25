//
//  main.c
//  lab1
//
//  Created by Adelia on 18.01.2021.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, const char * argv[]) {
    printf("my id is %d\nmy group id is %d\n", (int)getuid(), (int)getgid());
    return 0;
}
