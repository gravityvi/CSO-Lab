/* pipe1.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    int pipefds[2];
    char buf[30];
    //create pipe
    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    //write to pipe
    printf("writing to file descriptor #%d\n", pipefds[1]);
    write(pipefds[1], "IT215", 6);
    //read from pipe
    printf("reading from file descriptor #%d\n", pipefds[0]);
    read(pipefds[0], buf, 6);
    printf("read \"%s\"\n", buf);
    return 0;
}
