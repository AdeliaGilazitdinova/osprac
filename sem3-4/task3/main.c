//
//  main.c
//  task3
//
//  Created by Adelia on 08.02.2021.
//

#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("COMMAND LINE ARGUMENTS:\n");
    for (int i = 0; i < argc; i++) {
        if(i == 0)
            printf("[0] program name = %s\n", argv[i]);
        else
            printf("[%d] = %s\n", i, argv[i]);
    }
    printf("ENVIRONMENT VARIABLES:\n");
    int i = 0;
    while(envp[i] != NULL){
        printf("[%d] = %s\n", i, envp[i]);
        i++;
    }
    return 0;
}
