#include <stdlib.h>
int *add_sum(void);
int *add_sum(void)
{
	int *p;
	p=malloc(sizeof(int));
	*p=(1+100)*100/2;
	return p;
}
