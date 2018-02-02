#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>
#include <string.h>

pid_t pid;

void handler( int sig )
{
	if( pid == 0 )
	{
		printf( "Signal received by child %d\n" , sig );
	}
	else
	{
		printf( "Signal received by parent %d\n" , sig );
		kill( pid , SIGKILL );
		wait( NULL );
		printf( "parent will exit now\n" );
		exit(0);
	}
}

void overwrite_handler()
{
	for( int i = 1 ; i <= 31 ; i++ )
	{
		if( signal( i , handler ) == SIG_ERR )
			if( i == 9 ) perror( "9" );
			else perror( "19" );
	} 
}

int main()
{
	if( ( pid = fork() ) == 0 )
	{
		overwrite_handler();
		
		while(1)
		{
			printf( "child waiting\n" );
			sleep(1);
		}
	}
	
	if( pid == -1 )
	{
		printf( " Fork Error! \n " );
		exit(0);
	}
	
	overwrite_handler();
	
	srand( ( unsigned ) getpid() );
	sleep(2);
	
	int sig;
	while(1)
	{
		sig = rand() % 31 + 1;
		printf( "parent sending signal %d\n" , sig );
		kill( pid , sig );
		sleep(1);
	}
	
	return 0;
}
