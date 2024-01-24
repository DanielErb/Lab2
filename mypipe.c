#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {

    int p[2];
    char msg[16];
    if (pipe(p) < 0)
        exit(1);

    int pid = fork();
    if (pid > 0) {
        write(p[1], "hello", 16);
        exit(1);
    }
    waitpid(pid, NULL, 0);
    read(p[0], msg, 16);
    printf("%s\n", msg);
}

    //ls | grep pipe
