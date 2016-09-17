
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void signal_callback_handler(int segnum)
{
	printf("ExetinG!!: %i \n", segnum);

}

int fork2(void)
{
	pid_t pid = getpid();
	pid_t cpid, mypid,tcpid,tpid;
	
	printf("Parent PID: %i \n", pid);
	
	cpid=fork();
	tpid=fork();//????
	
	signal(SIGINT, signal_callback_handler);
	int status;
	
	if (cpid>0)
		{
		mypid=getpid();
		
		printf("[%i] parent of [%i]\n", mypid,cpid);
		tcpid = wait(&status);
		printf("[%i] bye [%i]\n", mypid,cpid);
		}
	
	if (cpid==0)
		{
		mypid=getpid();
		printf("I am a child with PID [%i] \n", mypid);
		}

	while (1)
		{
		
		}
	return 0;
}