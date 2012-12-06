#include <stdio.h>
void jmp(void)
{
	printf("This is in function jmp\n");
}
int main(void)
{
	printf("This is man and you can not call function jmp\n");
	return 0;
}
