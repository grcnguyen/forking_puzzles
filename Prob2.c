// Grace Nguyen
// 01-2017
// COEN177
// Assignment 1.2
/*
	The following code launches a chain of 8 processes. The original process forks.
	Then, the current process id is checked to see if the process is currently the
	parent or the child. If the process is the parent, it waits for its child to
	terminate. If it is the child, it forks again, producing grand child. Once again,
	the new parent waits on its child to terminate before it terminates. This repeats
	until there are 8 processes in total. Then, the youngest child dies, causing its
	parent to terminate, and thus the parent before it to terminate, and so on until
	all processes terminate.
	
	To test, a print statement is added to print out the current process child's PID
	along with its parent's PID. When run, the expected outcome should be the PID
	of the initial process along with the PIDS of 7 of its children (for a total of 8).
	To check if each process really produced only one child, make sure that the parent
	pid for any one process is the same as the pid of the process before it.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int i, pid;
	printf("Initial PID: %d\n", getpid());
	for (i=0; i<7; ++i)
	{
		pid = fork();
		if (pid!=0) //if a parent
		{		
			waitpid(pid, NULL, 0);    //wait for child to die
			exit(0);
		}
		else
		{
			printf("%d lives! Parent: %d  PID: %d\n", i+1, getppid(), getpid());
		}	
	}
	
}
