#include<stdio.h>

int main()
{
	if(fork()==0)
	{
		//B child process created
	}

	else//parent process
	{
		if(fork()==0)
		{
			//process D created
			if(fork()==0)
			{
				//process G created
			}
		}
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
	}
}
