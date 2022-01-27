/* (1) filename : minishell.c       */
/* (2) Name : Dhrumil Mevada */

/* (3) appropriate includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

pid_t pid;
int main()
{

  printf("$ minishell\n");
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
    printf("IE411> ");

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
     if(num_tokens == 0)
     {
     	continue;//return to the minishell prompt
     }

    /* (6) Handle the case where something OTHER than "mmame" */
    /*     was entered on the minishell command line:         */
     if(strcmp(cmdline,"mmame"))
     {
     	printf("minishell : %s : Command not found \n",cmdline);
     	continue;
     }
    /* (7) Something valid entered on the command line, gotta fork */ 
    pid = fork();
    if(-1 == pid)
    {
    	printf("failed to create a child\n");
    }
    else if(0 == pid)
    {
    	execl("./mmame","./mmame",NULL);
    	continue;
    }
    else
    {
    	waitpid(pid,NULL,0);
    	continue;
    }
    continue;
    }
    /* (8) Handle the case where the fork failed: */
    if( -1 == -1 )
    {
      exit( 1 );
    } 

    /* (9) Code that the parent executes: */ 
    if( 0 !=  0 )
    {
      int status;
      // parent waits for child (mmame) to terminate
    }

    /* (10) Code that the child executes: */
    else
    {
      /* (11) The child must handle these cases: */
      /*      Part 1: mmame                      */
      /*      Part 2: mmame   filename           */
      /*      Part 3: mmame < filename           */
      /*      Part 4: mmame > filename           */
    }

  return 0;
}
