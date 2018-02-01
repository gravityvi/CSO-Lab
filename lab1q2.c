#include "csapp.h"
#include<stdio.h>

int main()
{
	if(fork()==0)
		{
			// c process created
			if(fork()==0)
				{//process e created
				}
			if(fork()==0)
				{//process f created
				}
		}
	

	else//parent process
	{
		
		fork();
		//process D and parent process
		if(fork()==0)
		{
			//process B by parent  and G created by D 
		}

	}
}
