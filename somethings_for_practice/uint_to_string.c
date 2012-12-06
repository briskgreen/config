#include <time.h>
#include <stdio.h>
#include <stdlib.h>
char *uint_to_string(time_t t)
{
	int i=1;
	time_t temp=t;
	char *buf;
	while(temp>10)
	{
		temp/=10;
		i++;
	}
	buf=malloc(sizeof(char)*i);
	buf[i]='\0';
	while(i)
	{
		buf[--i]=t%10+'0';
		t/=10;
	}
	return buf;
}
int main(void)
{
	time_t t;
	char *buf;
	t=time(NULL);
	buf=uint_to_string(t);
	printf("t=%u buf=%s\n",t,buf);
	free(buf);
	return 0;
}
