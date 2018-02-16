/* (1) filename          */
/* (2) last name, first name */

/* (3) appropriate includes */
#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include <fcntl.h>

int main()
{
  while( 1 )
  {
/* ==== DO NOT MODIFY ANY OF THESE DECLARATIONS ============ */
    char cmdline[1024];  // the entire minishell command line
    int  num_tokens = 0; // number of tokens on the minishell command line
    char tokens[3][256]; // an array of the tokens
    int i = 0;           // just a counter
    char *p;             // pointer for stepping thru tokens
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

    /* (4) Print the minishell prompt: */
    printf("IT215>");

/* ==== DO NOT MODIFY THIS NEXT SECTION OF CODE ============ */
    /* This reads an entire line from stdin: */
    if( fgets( cmdline, 1024, stdin ) == NULL ) { printf("\n"); break; }

    // This replaces the newline at the end of the string with a NULL
    *strrchr( cmdline, '\n') = '\0';

    // extract the individual tokens from the minishell command line
    p = cmdline;
    while( 1 == sscanf( p, " %s", tokens[i] ) )
    {
      p = strstr( p, tokens[i] ) + strlen( tokens[i] );
      ++i;
    }
    num_tokens = i;
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */

    /* (5) Handle the case where there were no tokens on the
     * minishell command line, i.e., maybe the user just
     * hit the ENTER key:
     */
    if(num_tokens==0)
    {
      continue;
    }


    /* (6) Handle the case where something OTHER than "mmame" */
    /*     was entered on the minishell command line:         */
    if(strcmp(tokens[0],"mmame")!=0)
    {
      printf("minishell: %s  : command not found\n",tokens[0]);
      continue;
    }
    

    /* (7) Something valid entered on the command line, gotta fork */
    pid_t cpid;
    cpid=fork();


    /* (8) Handle the case where the fork failed: */
    if( cpid == -1 )
    {
      exit( 1 );
    } 

    /* (9) Code that the parent executes: */ 
    if( cpid !=  0 )
    {
      int status;
      // parent waits for child (mmame) to terminate
      waitpid(cpid,&status,0);
    }

    /* (10) Code that the child executes: */
    else
    {
      /* (11) The child must handle these cases: */
      /*      Part 1: mmame                      */
      if(num_tokens==1)
      {
        char *args[2];
        args[0]="./mmame";
        args[1]=NULL;
        execv("./mmame",args);
      }
      
      /*      Part 2: mmame   filename           */
      else if(num_tokens==2)
      {
        char *args[3];
        args[0]="./mmame";
        args[1]=tokens[1];
        args[2]=NULL;
        execv("./mmame",args);
      }

      
      /*      Part 3: mmame < filename           */

      else if(num_tokens==3&&strcmp(tokens[1],"<")==0)
      {
        close(0);
        int fd;
        fd=open(tokens[2],O_RDONLY,0);
        char *args[3];
        args[0]="./mmame";
        args[1]=tokens[2];
        args[2]=NULL;
        execv("./mmame",args);
        close(fd);

      }

      /*      Part 4: mmame > filename           */

        else if(num_tokens==3&&strcmp(tokens[1],">")==0)
      {
        close(1);
        int fd;
        fd=open(tokens[2],O_CREAT|O_TRUNC|O_RDWR,0644);
        char *args[3];
        args[0]="./mmame";
        args[1]=tokens[2];
        args[2]=NULL;
        execv("./mmame",args);
        close(fd);

      }


    }

  }
  return 0;
}
