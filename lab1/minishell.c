/* (1) minishell.c         */
/* (2) Mevada Dhrumil Bipinchandra (201901128)*/

/* (3) appropriate includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include<fcntl.h>
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
     if(num_tokens==0) 
     {
     	continue;  //returns to the minishell prompt
     }
      //forking 
      pid = fork();
      if (-1 == pid)
      {
        exit(1);
      }
      if( pid !=  0 )
     {
      int status;
      wait(&status);
      // parent waits for child (mmame) to terminate
     }
    
    else
    {
    	if(num_tokens==1)   
    	{
    		if(strcmp(cmdline,"mmame"))   //something other than mmame is written on the command prompt
     		{
     			printf("minishell : %s : Command not found \n",cmdline);
     			continue;
     		}
     		else // mmame is written on the command prompt
     		{
     			execl("./mmame", "./mmame",NULL); 
     			continue;
     		}
     			
    	}
    	else if(num_tokens==2)  //mmame with the test_data.dat file (any input file)
      	{
      		char *args[]={"./mmame",tokens[1],NULL}; 
      		   		
        	if(execvp(args[0],args))
        	{
        		continue;
        	}
        	else
        	{
        		printf("minishell : %s : Command not found \n",cmdline);
     			continue;
        	}
      	}
      	else if(num_tokens == 3)
        {
        	if(strcmp(tokens[1], "<") == 0)  //mmame reading from directly from test_data.dat file  (any input file)
        	{        		
	 		
	 		int filefd = open(tokens[2], O_RDONLY, 0666); //opening input file
	 		if(filefd== -1)
	 		{
	 			printf("Input file doesn't exist\n");
	 			continue;
	 		}
		        if (!fork()) 
			{
			  close(0);//Close stdin
			  dup(filefd);
  	                 
  	                 char *args[]={"./mmame",NULL};  
	  		  execvp(args[0],args);
		          printf("minishell : %s : command not found\n",tokens[0]); 
			} else 
			{
			  close(filefd);
			  wait(NULL);
			}  
        	}
        	else if(strcmp(tokens[1],">") == 0)  // writting to foo.dat file insted of stdout
        	{
			int filefd = open(tokens[2], O_WRONLY|O_CREAT, 0666);
			if (!fork()) 
			{
			  close(1);//Close stdout
			  dup(filefd);
  	      
  	                 char *args[]={"./mmame",NULL};  
	  		  execvp(args[0],args);
		          printf("minishell : %s : command not found\n",tokens[0]); 
			} else 
			{
			  close(filefd);
			  wait(NULL);
			} 
		}      
		else
		{
		        printf("minishell : %s : command not found\n",tokens[1]);   
		}  	
        }
      }
    	continue;
    }
return 0;
  }
