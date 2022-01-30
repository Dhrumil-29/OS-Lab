/* (1) minishell.c         */
/* (2) Dhrumil Mevada	*/

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
     if(num_tokens == 0)
     {
     	 continue;  //returns to the minishell prompt
     }
      
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
    /* (6) Handle the case where something OTHER than "mmame" */
    /*     was entered on the minishell command line:         */
    else
    {
    	if(num_tokens == 1)
    	{
    		//only mmame enter
    		if(strcmp(cmdline,"mmame"))
     		{
     			//mmame didn't write by user
     			printf("minishell : %s : Command not found \n",cmdline);
     			continue;
     		}
     		else
     		{
     			//run mmame run
     			execl("./mmame", "./mmame",NULL);
     			continue;
     		}
     			
    	}
    	else if(num_tokens == 2)
      	{
      		//take inputs from files
      		char *args[]={"./mmame",tokens[1],NULL}; 
      		//token[1] = file name in which programe take inputs
      		   		
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
        	//Input-Output Redirection...
        	if(strcmp(tokens[1], "<") == 0)
        	{        		
	 		//char *args[]={buff,tokens[2],NULL};
	 		char *args[]={"./mmame",tokens[2],NULL};  
	  		execvp(args[0],args);
		        printf("minishell : %s : command not found\n",tokens[0]);  
        	}
        	else if(strcmp(tokens[1],">") == 0)
        	{
        		int filefd = open(tokens[2], O_WRONLY|O_CREAT, 0666);
			//int filefd = open("foo.dat", O_WRONLY|O_CREAT, 0666);
			if (!fork()) 
			{
			   close(1);//Close stdout
			   dup(filefd);
  	                  //char *args[]={buff,NULL}; 
  	                   char *args[]={"./mmame",NULL};  
	  		   execvp(args[0],args);
			   printf("minishell : %s : command not found\n",tokens[0]); 
			} 
			else 
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
     
     
    /* (7) Something valid entered on the command line, gotta fork */
	 
      
     // else if (0 == pid)
    //  {
        
        
        
      //  continue;
      //}
      //else
      //{
        
      //    waitpid(pid, NULL, 0);
      //  continue;
      //}
      //continue;
    //}	
    /* (8) Handle the case where the fork failed: */
 /*   if( -1 == -1 )
    {
      exit( 1 );
    } 

    /* (9) Code that the parent executes: */ 
    //if( 0 !=  0 )
    //{
      //int status;
      // parent waits for child (mmame) to terminate
    //}

    /* (10) Code that the child executes: */
    //else
   // {
      /* (11) The child must handle these cases: */
      /*      Part 1: mmame                      */
      /*      Part 2: mmame   filename           */
      /*      Part 3: mmame < filename           */
      /*      Part 4: mmame > filename           */
   //}*/
   
return 0;
  }
