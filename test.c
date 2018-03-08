#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
    int pipefds[2];
    pipe(pipefds);

    dup2(pipefds[0],STDIN_FILENO);
    dup2(pipefds[1],STDOUT_FILENO);
    close(pipefds[0]);
    close(pipefds[1]);

    int n = 98;
for( int i = 0; i < 10; i++ ) {
write( STDOUT_FILENO, &i, sizeof(i) );
read( STDIN_FILENO, &n, sizeof (n) );
fprintf( stderr, "%d\n", n );
}

}