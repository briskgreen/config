#include <stdio.h>
void reverse(const char *s1,char *s2)
{
	while(*s1++);
	s1=s1-2;
	while(*s1)
		*s2++=*s1--;
	*s2='\0';
}
int main(void)
{
	char *s1="123456789";
	char s2[15];
	//printf("s1=%s %p\n",s1,s2);
	reverse(s1,s2);
	//printf("%p\n",s2);
	printf("s1=%s s2=%s\n",s1,s2);
	return 0;
}
