// Grace Nguyen
// 01-2017
// COEN177
// Assignment 1.3
/*
	To produce 12 processes, we will create a ternary process tree where two of the
	last nodes are 3-nodes and the last node is a 2-node as shown below:
	
	                	              x
	                    	       /  |  \
	                        	  x   x   x
	              	             /|\ /|\ / \
	                            x xx xxx x  x
	                        
	This code first creates a ternary process tree consisting of a parent node and 
	its three children. As each of the children are created, their pid is stored, and
	they are set to wait for their children to terminate. The first child that is 
	created is also marked child1, and this will be root of the 2-node. The other 
	two children will be 3-nodes. After creating the first level, we check to see if 
	any of the saved pids are == 0, which indicates that it isn't the initial process. 
	(The first process's pida, pidb, and pidc variables will all be non-zero). The 
	processes where pida==0||pidb==0||pidc==0 and are NOT marked as child1 are spawned 
	a final 3 children, which are immediately terminated, thus terminating their parent.
	The process where pida==0||pidb==0||pidc==0 and is marked child1 is made to spawn
	2 children, which are immediately terminated, thus terminating the parent process.
	After all 3 children to the initial process are terminated, the initial process 
	will itself terminate.
	
	Testing was done by writing a print statement for each child process created.
	This print statement will also print the current PID and the parent's PID. Use
	this information to trace the tree and see that it follows the format illustrated
	above to produce a total of exactly 12 processes.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int i;
	int pida, pidb, pidc, first;
	int child1 = 0;
	
	first = getpid();
	printf("Starting PID: %d\n", first);
	
	pida = fork(); //creates one child
	if (pida != 0) //creates two more children if current process is parent
	{	
		pidb = fork();
		if (pidb !=0){
			pidc = fork();
			if (pidc==0) //parent
			{ 
				waitpid(pidc, NULL, 0);
				waitpid(pidb, NULL, 0);
				waitpid(pida, NULL, 0);
				printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());
			}
		}
		else 
		{
			waitpid(pidc, NULL, 0);
			waitpid(pidb, NULL, 0);
			waitpid(pida, NULL, 0);
			printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());
		}
	}
	else 
	{
		child1 = 1;
		waitpid(pidb, NULL, 0);
		waitpid(pida, NULL, 0);
		printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());
	}	

	/* Adds 3 children to all but one leaves in the ternary tree*/
	if((pida==0||pidb==0||pidc==0)&&(child1 == 0))
	{
		if ((pida=fork())!= 0) //if parent, fork again. Goal is for this parent to have 3 children
		{
			if ((pidb=fork()) != 0)
			{
				if ((pidc=fork()) == 0)
				{
					printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());
					exit(0);
				}
			}
			else 
			{
				printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());		
				exit(0);
			}
		}
		else 
		{
			printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());			
			exit(0);
		}
	}
	
	/*Adds 2 children to the one leaf in the ternary tree*/
	else if ((pida==0||pidb==0||pidc==0)&&(child1 == 1))
	{
		if ((pida=fork())!= 0) //if parent, fork again for a total of 2 children
		{
			if ((pidb=fork())== 0)
			{
				printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());
				exit(0);
			}
		}
		else 
		{
			printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());		
			exit(0);
		}
	}
	
	waitpid(pidc, NULL, 0);
	waitpid(pidb, NULL, 0);
	waitpid(pida, NULL, 0);		
}


