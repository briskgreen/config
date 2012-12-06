#include <stdio.h>
unsigned int string_to_uint(char *s)
{
	int i;
	unsigned int t=0;
	for(i=0;s[i];i++)
	{
		t*=10;
		t+=s[i]-'0';
	}
	return t;
}
int main(int argc,char **argv)
{
	char *s="135395401";
	unsigned int t;
	t=string_to_uint(s);
	printf("%u %s\n",t,s);
	return 0;
}
