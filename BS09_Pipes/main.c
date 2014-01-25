//
//  main.c
//  BS09_Pipes
//
//  Created by Markus Klemm on 25.01.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include <stdio.h>
#include <string.h>

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
    
    char cbuff[buffsize];
    
    do {
        fgets(cbuff, buffsize, stdin);
        
        char input[strlen(cbuff)+1];
        strcpy(input, cbuff);
        
        int i;
        for (i=0; i < strlen(input); i++) {
            input[i] = rot13(input[i]);
        }
        
        printf("%s",input);
        
    } while (strstr(cbuff, "quit") == NULL);
    
    
    return 0;
}

