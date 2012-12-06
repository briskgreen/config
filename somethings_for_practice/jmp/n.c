#include <stdio.h>
int main(void)
{
	int a=0x080483ed+5;
	int b=0x080483c4;
	int c=a-b;
	printf("%#x\n",c);
	c=~c;
	c+=1;
	printf("%#x\n",c);
	return 0;
}
