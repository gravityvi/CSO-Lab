#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
//1 for parent
//2 for process c
//3 for process d
//4 for process e
//5 for process f

void main()
{

    int sample=0;
    pid_t pid;
    char cmd[20];
    pid = getpid();
    if(fork()==0)
    {
        sample=2;//process c 
    }
    else
    {
        sample=1;//parent process
    }
    if(fork()==0)
    {
        if(sample==1)
        {
            sample=3;//process d
        }
        else if(sample=2)
        {
            sample=4;//process e
            
        }
    }
    else
    {

    }
    if(sample==1||sample==2||sample==3)
    {
        if(fork()==0)
        {
            while(1);//process f , process b , process g 
        }
	else
	{
		//while(1); //process c, process a or parent ,process d
	}
    }
    else
    {
        while(1);//process e
    }

    getc(stdin);
    sprintf(cmd,"pstree -p  %d\n",pid);
    system(cmd);
    kill(-pid,SIGKILL);

}
