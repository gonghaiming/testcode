//
//  main.c
//  codetest
//
//  Created by MR_gong on 2/10/17.
//  Copyright © 2017 gong. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include<sys/types.h>
#include "parseCmd.h"
#include <stdlib.h>
#include <signal.h>
#define MAX_LINE 80
void cmdHandleTask(int sendfd, int recvFd);
void cmdSendTask(int sendFd, int recvFd, pid_t pid);
void printtask();
int main(int argc, const char * argv[])
{
    int ret;
    int cmdSendFd[2];
    int cmdHandleFd[2];
    pid_t pid;
    ret = pipe(cmdSendFd);
    if (ret < 0)
    {
        printf("cmdSendFd create error");
    }
    
    ret = pipe(cmdHandleFd);
    if (ret < 0)
    {
        printf("cmdHandleFd create error");
    }
    
    pid = fork();
    
    if (pid < 0)
    {
        printf("fork error");
    }
    
    if (pid == 0)
    {
        //fork child process
        close(cmdHandleFd[0]);
        close(cmdSendFd[1]);
        cmdHandleTask(cmdHandleFd[1], cmdSendFd[0]);
        
        
    }
    
    close(cmdHandleFd[1]);
    close(cmdSendFd[0]);
    cmdSendTask(cmdSendFd[1], cmdHandleFd[0], pid);
    return 0;
}

void cmdHandleTask(int sendfd, int recvFd)
{
    char recvMsg[MAX_LINE];
    int len = 0;
    char c;
    
    pid_t pid;
    
    pid = fork();
    if (pid < 0)
    {
        return;
    }
    if (pid == 0)
    {
        //child process
        
        sleep(1);
        printtask();
    }
    //parent process
    
    kill(pid, SIGSTOP);
    while(1)
    {
        len = read(recvFd, recvMsg, MAX_LINE);
        if (len < 0)
        {
            printf("pipe read error");
        }
        printf("recvMsg = %s", recvMsg);
        parseCmd(recvMsg, pid);
        
        write(sendfd, &c, 1);
        
    }
    return;
}
void cmdSendTask(int sendFd, int recvFd, pid_t pid)
{
    char sendMsg[MAX_LINE];
    int len = 0;
    char c;
    
    while(1)
    {
        printf(">>");
        fgets(sendMsg, MAX_LINE, stdin);
        len = strlen(sendMsg);
        c = sendMsg[len-1];
        if ( c  == '\n')
        {
            sendMsg[len] = '\0';
        }
        write(sendFd, sendMsg, MAX_LINE);
        
        read(recvFd, &c, 1);
    }
    
    
    return;
}
void printtask()
{
    while(1)
    {
        printf("\nhello");
        sleep(1);
    }
}
