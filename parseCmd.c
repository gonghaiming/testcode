//
//  parseCmd.c
//  codetest
//
//  Created by MR_gong on 2/10/17.
//  Copyright © 2017 gong. All rights reserved.
//

#include "parseCmd.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>


void parseCmd(char *cmd, pid_t pid)
{
    char *delim = " ";
    char *p;

    p = strtok(cmd, delim);
    printf("%s\n", p);
    while(p)
    {
        if ( strcmp( p, "prime") == 0)
        {
            printf("\n%s", p);
            p = strtok(NULL, delim);
            
            if ( strcmp( p, "start\n") == 0)
            {
            printf("\n%s ", p);
                
                kill(pid, SIGCONT);
                
            }
            else if (strcmp(p , "stop\n") == 0)
            {
                kill(pid, SIGSTOP);
                
            }
            else if ( strcmp( p , "contine\n") == 0)
            {
                kill(pid, SIGCONT);
            }
            else if ( strcmp(p, "exit\n") == 0)
            {
                kill(pid, SIGINT);
                
            }
            else
            {
                printf("not suportted cmd\n");
                break;
            }

        }
        break;
        
    }
}

