
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int file1(void)
{
	int fname = open("/Users/sergey/Documents/programming/cs50git/os/file1.c", O_WRONLY | O_APPEND);
	int fname2 = open("/Users/sergey/Documents/programming/cs50git/os/fork1.c", O_WRONLY | O_APPEND);
	
	printf(" fname= %lu \n",sizeof("blablablsd"));
	printf(" fname2= %i \n",fname2);
	
	//write(fname2, "testing", sizeof("testing"));
	
	
	close(fname);
	close(fname2);
	//char wait;
	getchar();
	
  	return 0;
}

