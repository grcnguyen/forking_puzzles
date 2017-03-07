// Grace Nguyen
// 01-2017
// COEN177
// Assignment 1.4
/*
	To produce 1b processes, we will create a binary process tree with a depth of
	2. Of the 4 leaves, three of them will have 3 children each, and the final child
	will have no children of its own. The structure will appear as so:
	
										x
									 /     \
								   o		 x
								 /   \     /   \
								o     o   o     x
							   /|\   /|\ /|\
							  x x x x xx xx x
	
	The following code first generates the full generations in the binary tree.
	In this case, 2 new generations of children are spawned from the initial process
	by forking the process, checking if it is the parent, and if it is the parent,
	creating a second fork. The PIDs of the children are stored. After a parent has 
	two children, the parent's pida and pidb values will NOT be 0. Use this test to 
	identify parents and put them to sleep after they have spawned both of their 
	children. When forking off the first child, the child is marked as child1, which
	will play a role in deciding which of the 3 leaves will spawn 3 children each.*
	When we leave the loop, we ensure that i==2, indicating that we're on the 
	incomplete row of the tree. If the leaf is marked as child1, it produces 3 children,
	which are immediately terminated to terminate its parent. If the leaf is not
	marked as a child, it terminates. These terminations cascade to the top, eventually
	terminating the initial process.
	
	Testing was done by writing a print statement for each child process created.
	This print statement will also print the current PID and the parent's PID. Use
	this information to trace the tree and see that it follows the format illustrated
	above to produce a total of exactly 16 processes.
	
	*child1 works because all of the children of the first child marked child1 will 
	also be marked as child1. Because this tree is only 2 generations deep, the number
	of children in the last full row will be 4 (2^2). The two children of the very
	first child will be marked as child1. As well, the first child of the second 
	process to fork off the initial process will also be marked child1, giving a total
	of three children marked child1. Only 3 leaves have to produce 3 children each
	in order to solve this problem. (The nodes marked child1 are represented by o's
	in the diagram above.)
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int i;
	int pida, pidb, pidc, first;
	int child1 = 0; //keeps track of which child is created first
	
	first = getpid();
	printf("Starting PID: %d\n", first);
	
	/*Generates complete generations in Binary Process Tree*/
	for(i=0; i<2; ++i)
	{	
		pida = fork(); //creates one child
		if (pida != 0) //creates another child if current process is parent
		{	
			pidb = fork();
		}
		else
			child1 = 1;
		
		if (pida!=0 && pidb!=0) //if parent, wait for children to terminate
		{ 
			waitpid(pidb, NULL, 0);
			waitpid(pida, NULL, 0);
        	exit(0);
		}
		printf("Parent PID = %d, THIS PID = %d\n", getppid(), getpid());
	}
	
	/* Adds 3 children to select children in last generation*/
	if(i==2 && child1 == 1)
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
	else if (i==2)
	{		
		exit(0);
	}
	
	waitpid(pidc, NULL, 0);
	waitpid(pidb, NULL, 0);
	waitpid(pida, NULL, 0);
}


