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

/*inline*/ void rot13(char* restrict torotate)
{
    if ('A' <= *torotate && *torotate <= 'Z') {
        *torotate = (*torotate -'A'+13)%26 + 'A';
    }
    else if ('a' <= *torotate && *torotate <= 'z')
    {
        *torotate = (*torotate -'a'+13)%26 + 'a';
    }
}

int main(int argc, const char * argv[])
{
    
    char cbuff[buffsize];
    fgets(cbuff, buffsize, stdin);
    
    int i;
    
    for (i=0; i < strlen(cbuff); i++) {
        rot13(&cbuff[i]);
    }

    printf("%s\n",cbuff);
    
    return 0;
}

