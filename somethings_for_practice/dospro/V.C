#include <stdio.h>
int size(const char *s1,char *s2)
{
	s2=(char *)s1;
	while(*s1++);
	return s1-s2;
}
void recv(const char *s1,char *s2)
{
	s2+=size(s1,s2)-1;
	*s2='\0';
	while(*s1)
		*--s2=*s1++;
}
int main(void)
{
	char s1[15]="123456789";
	char s2[15];
	recv(s1,s2);
	printf("s1=%s s2=%s\n",s1,s2);
	return 0;
}