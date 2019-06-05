#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	
	int child = 0;
	char memory[30];
	char input[20];
	char *token;
	char *arg_arr[30];

	scanf("%[^\n]s", input);
	int x = strcmp("quit", input);
	int arguments = 0;
	
			
	while (x != 0)
	{
		token = strtok(input, " ");
		
		while (token != NULL) 
		{
			arg_arr[arguments++] = token;
			token = strtok(NULL, " ");
		}
		
		child = fork();
    			
		if (child == 0) 
		{
			if (execvp(*arg_arr, arg_arr) < 0) 
			{ 
				return 1;
         	}
     	}	
    			 
    	else
		{                         
        	wait(&child);
			execvp(argv[0], argv);	
   		}
		
	}		
	
	return 0;	
} 