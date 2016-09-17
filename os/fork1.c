
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int fork1(void)
{
	pid_t pid = getpid();
	pid_t cpid, mypid;

	printf("Parent PID: %i \n", pid);
	
	cpid=fork();
	
	if (cpid>0)
	{
		mypid=getpid();
		printf("[%i] parent of [%i]\n", mypid,cpid);
	}

	if (cpid==0)
	{
		mypid=getpid();
		printf("[%i] child\n", mypid);
	}
	printf(" PID= %i \n",cpid);
	
  	return 0;
}