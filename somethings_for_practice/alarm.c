#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define MUSIC "/home/brisk/Music/QQ爱.mp3"
typedef struct
{
	int s;
	int m;
	int h;
	int date;
}TIME;
void child_run(TIME *alarm)
{
	setsid();
	chdir("/");
	int fd;
	long sleep_time;
	if((fd=open("/dev/null",O_RDWR))==-1)
		exit(1);
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDIN_FILENO);
	dup2(fd,STDERR_FILENO);
	close(fd);
	//close(STDOUT_FILENO);
	//close(STDIN_FILENO);
	//close(STDERR_FILENO);
	time_t t;
	long sec;
	struct tm *ti;
	//sec=alarm->h*3600+alarm->m*60+alarm->s;
	t=time(NULL);
	ti=localtime(&t);
	alarm->h+=(alarm->date-ti->tm_mday)*24;
	sec=alarm->h*3600+alarm->m*60+alarm->s;
	sleep_time=sec-(ti->tm_hour*3600+ti->tm_min*60+ti->tm_sec);
	if(sleep_time>0)
		sleep(sleep_time);
	else
		exit(1);
	//sleep(sec-(ti->tm_hour*3600+ti->tm_min*60+ti->tm_sec));
	if(fork()==0)
		execl("/usr/bin/mplayer","mplayer",MUSIC,NULL);
	exit(0);
}
void again(void)
{
	printf("输入有误,请重新输入:");
	while(getchar()!='\n')
		continue;
}
int main(void)
{
	TIME alarm;
	printf("输入日期:");
	while(scanf("%d",&alarm.date)==0||alarm.date>31)
		again();
	printf("请输入小时:");
	while(scanf("%d",&alarm.h)==0||alarm.h>=24)
		again();
	printf("请输入分钟:");
	while(scanf("%d",&alarm.m)==0||alarm.m>=60)
		again();
	printf("请输入秒数:");
	while(scanf("%d",&alarm.s)==0||alarm.s>=60)
		again();
	if(fork()==0)
		child_run(&alarm);
	return 0;
}
