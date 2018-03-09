#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
    int p1[2];
    int p2[2];
    int p3[3];
    int p4[4];
    pid_t pid1,pid2,pid3;

    pipe(p1);
    pipe(p2);
    pipe(p3);
    pipe(p4);

    if((pid1=fork())==0) //child 1
    {
        close(p2[0]);
        close(p2[1]);
        close(p3[0]);
        close(p3[1]);
        close(p4[1]);
        close(p4[0]);
        close(p1[1]);
        
        char buff1[30];
        int count=0;

        while(read(p1[0],&buff1,1)==1)
        {
            if(count==0)
            {
                printf("child 1 is printing: ");
            }
            if(buff1[0]=='\0')
            {
                count=0;
                printf("\n");
                continue;
            }
            count=1;
            printf("%s",buff1);   
            fflush(stdout);
        }
        
        
        exit(1);
    }

    if((pid2=fork())==0)//child 2
    {
        close(p1[0]);
        close(p1[1]);
        close(p3[0]);
        close(p4[1]);
        close(p2[1]);

        char ch;
        
        
            
            char buff2[30];
            int count=0;
             while(read(p2[0],&buff2,1)==1)
            {
                if(count==0)
            {
                if(buff2[0]=='3')
                {
                    char ch1='r';
                    write(p3[1],&ch1,1);
                    char ch2;
                    read(p4[0],&ch2,1);
                    continue;
                    
                }
                else{
                printf("child 2 is printing: ");}
                
            }
            if(buff2[0]=='\0')
            {
                count=0;
                printf("\n");
                continue;
            }
                count+=1;
                if(count==1)
                {continue;}
                printf("%s",buff2);   
                fflush(stdout);
            }
        
        
        

        
        close(p3[1]);
        close(p4[0]);
        close(p2[0]);
        exit(2);
    }

    if((pid3=fork())==0)//child 3
    {

        close(p1[0]);
        close(p1[1]);
        close(p3[1]);
        close(p4[0]);
        close(p2[1]);

        char ch1;
       outer: while(1)
        {
        read(p3[0],&ch1,1);
        if(ch1=='r')
        {
             char buff2[30];
             int count=0;
             while(read(p2[0],&buff2,1)==1)
            {

                   if(count==0)
                    {
                        printf("child 3 is printing: ");
                    }
                    if(buff2[0]=='\0')
                    {
                        count=0;
                        printf("\n");
                        int ch2='s';
                        write(p4[1],&ch2,1);
                        goto outer;
                    }
                count=1;
                printf("%s",buff2);   
                fflush(stdout);
            }
        }
        }

        close(p4[1]);
        close(p3[0]);
        exit(3);
    }
     
    //parent Process

    char buff[30];
    char ch;
    int n;
    int i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
    printf("Hello from parent, your message Please \n");
    scanf("%s %c",buff,&ch);
    
    
    if(ch=='1')
    {
        
        write(p1[1],&buff,strlen(buff)+1);
        
    }

    else
    {
        write(p2[1],&ch,1);
        write(p2[1],buff,strlen(buff)+1);
        
    
    }
    sleep(1);
    }

    close(p2[0]);
        close(p2[1]);
        close(p3[0]);
        close(p3[1]);
        close(p4[1]);
        close(p4[0]);
        close(p1[1]);
        close(p1[0]);
        waitpid(pid2,NULL,0);
        waitpid(pid3,NULL,0);
        waitpid(pid1,NULL,0);

}
