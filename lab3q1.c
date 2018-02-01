#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<string.h>

int alarm_count=0;

void Reverse(char* str)
{
	//reverse a string
	int i=0;
	int len=strlen(str);	
	for(i=len;i>=0;i--)
	{
		printf("%c",*(str+i));
		fflush(stdout);
	}
	printf("\n");
}

void handle_alarm(int sig)
{
	if(alarm_count==3)
	{
		printf("signal sent\n");
		kill(getpid(),SIGINT);
	}
	else
	{
	//alarm signal
	printf("Alert User Inactive\n");
	alarm_count++;
	printf("%d\n",alarm_count);
	alarm(10);
	}
}

int main()

{
	signal(SIGALRM,handle_alarm);
	while(1)
	{	
		alarm(10);
		char str[100];
		scanf("%s",str);
		alarm_count==0;
		alarm(10);
		Reverse(str);
	}

}
