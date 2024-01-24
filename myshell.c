#include <linux/limits.h>
#include <stdio.h>
#include "LineParser.h"
#include <signal.h>

int main(int argc, char **argv)
{
    char path[PATH_MAX];
    char input[2048];
    cmdLine *cmd;
    FILE * inputStream = stdin;
    int debug = 0;

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-d") == 0){
            debug = 1;
        }
    }

    while (1)
    {
        printf("Current working directory is: %s\n", getcwd(path, PATH_MAX));



        fgets(input, 2048, inputStream);
        cmd = parseCmdLines(input);

        if (debug)
        {
            fprintf(stderr, "PID: %d\n", getpid());
            fprintf(stderr, "Executing command: %s\n", cmd->arguments[0]);
        }

        if (strcmp(cmd->arguments[0], "quit") == 0)
        {
            freeCmdLines(cmd);
            break;
        }
        else if(strcmp(cmd->arguments[0], "cd") == 0){
            if (chdir(cmd->arguments[1]) == -1) {
                perror("Error");
            }
        }
        else if(strcmp(cmd->arguments[0], "nuke") == 0){
            kill(atoi(cmd->arguments[1]), SIGINT);
        }
        else if(strcmp(cmd->arguments[0], "wakeup") == 0){
            kill(atoi(cmd->arguments[1]), SIGCONT);
        }

        else{
            execute(cmd);
        }
    }
}

void execute(cmdLine *pCmdLine)
{
    int pid = fork();
    if (!pid)
    {
        if(pCmdLine->inputRedirect)
        {
            close(stdin);
            fopen(pCmdLine->inputRedirect, "r");
        }
        if(pCmdLine->outputRedirect)
        {
            close(stdout);
            fopen(pCmdLine->outputRedirect, "w");
        }
        execvp(pCmdLine->arguments[0], pCmdLine->arguments);
        perror("Error");
        exit(1);
    }
    if(pCmdLine->blocking)
        waitpid(pid, NULL, 0);

}