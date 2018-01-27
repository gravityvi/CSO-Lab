#include<stdio.h>

//1 for parent
//2 for process c
//3 for process d
 
 void main()
 {
     int sample=0;

    
     
         sample=1;
         if(fork()==0)
         {
             //process c
             sample=2;
         }
         else
         {
             sample=1;//for parent
         }
        if(fork()==0)
        {
            printf("%d\n",sample);
            if(sample==1)
            {
                if(fork()==0);
            }
        }
        else
        {
            if(sample==2||sample==1)
            {
                if(fork==0)
                    {//process e created
                    }
                    
            }
        }
         
     
 }