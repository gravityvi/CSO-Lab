#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>

int main()

{
	//first loop
	int i=0;
	sigset_t set1;
	sigaddset(&set1,SIGINT);
	sigaddset(&set1,SIGQUIT);
	sigprocmask(SIG_BLOCK,&set1,NULL);
	
	for(i=0;i<=5;i++)
	{
		printf("%d\n",i);
		sleep(1);
	}
	sigprocmask(SIG_UNBLOCK,&set1,NULL);

	sigdelset(&set1,SIGINT);
	sigprocmask(SIG_BLOCK,&set1,NULL);
	sleep(2);
	
	int j=0;	
	for(j=0;j<=5;j++)
	{
		printf("%d\n",j);
		sleep(1);
	}

}
