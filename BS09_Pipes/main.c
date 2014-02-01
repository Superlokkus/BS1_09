//
//  main.c
//  BS09_Pipes
//
//  Created by Markus Klemm on 25.01.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define buffsize 128

static inline char rot13(char torotate)
{
    if ('A' <= torotate && torotate <= 'Z') {
        return torotate = (torotate -'A'+13)%26 + 'A';
    }
    else if ('a' <= torotate && torotate <= 'z')
    {
        return torotate = (torotate -'a'+13)%26 + 'a';
    }
    return torotate;
}

int main(int argc, const char * argv[])
{
    printf("Please type in word which should be ROT13 encrypted or \"quit\"\n");
    int parent2child[2];
    if (pipe(parent2child)) {
        perror("Pipe failed");
        return EXIT_FAILURE;
    }
    
    pid_t mypid = fork();
    if (mypid < 0) {
        perror("Forking failed");
        return EXIT_FAILURE;
    }
    else if (mypid > 0)
    {
        //Parent
        if (close(parent2child[0])) {
            perror("closing reading descrpt failed");
            return EXIT_FAILURE;
        }
        
        char cbuff[buffsize];
        
        do {
            fgets(cbuff, buffsize, stdin);
            write(parent2child[1], cbuff, sizeof(cbuff));
            
        } while (strstr(cbuff, "quit") == NULL);
        
        if (close(parent2child[1])) {
            perror("Zombies!");
            return EXIT_FAILURE;
        }

    }
    else
    {
        //Child
        if (close(parent2child[1])) {
            perror("closing writeing descrpt failed");
            return EXIT_FAILURE;
        }
        while (true) {
            char input[buffsize];
            if (read(parent2child[0], input, sizeof(input)) <= 0) {
                close(parent2child[0]); //Failing isn't relevant,
                return EXIT_SUCCESS;
            }
            int i;
            for (i=0; i < strlen(input); i++) {
                input[i] = rot13(input[i]);
            }
            
            printf("%s",input);

        }
    }
    
    
    return 0;
}

