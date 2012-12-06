#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
void fun(void)
{
	//setreuid(0,0);
	execl("/bin/sh","sh",NULL);
}
int main(int argc,char **argv)
{
	char buf[5];
	strcpy(buf,argv[1]);
	printf("fun=%#x",fun);
	return 0;
}
