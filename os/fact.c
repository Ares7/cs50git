
#include <stdio.h>

int fact1(void)
{

	printf("%ju, ", sizeof(uintmax_t));
  	return 0;
}

void fib(void)
{
	uintmax_t m[100];
	m[0]=1;
	m[1]=1;
	
	for (int i=3; i<10; i++) {
		m[i-1]=m[i-2]+m[i-3];
		printf("%ju, ", m[i-1]);
	}
}
void fact2(void)
{
	uintmax_t myint;
	uintmax_t res=1;
	scanf("%ji", &myint);
	
	for (uintmax_t i=1; i<=myint; i++) {
		res=res*i;
	}
	
	
	printf("%ju", res);
}
