#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <myfun.h>
#include <errno.h>
#include <ncurses.h>
//#include <stdbool.h>
void error_quit(char *msg)
{
	perror(msg);
	exit(1);
}
int my_get(char *str,int size)
{
	int i=0;
	while((str[i]=getchar())!='\n'&&i<size)
		i++;
	if(i>=size)
		return 0;
	else
		str[i]='\0';
	return 1;
}
void my_continue(char *msg)
{
	struct termios new,old;
	if(tcgetattr(STDIN_FILENO,&old)==-1)
		error_quit("Get Terminal info Error!");
	new=old;
	new.c_lflag&=~ECHOFLAGSNONB;
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&new)==-1)
		error_quit("Set Terminal info Error!");
	printf("%s",msg);
	getchar();
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&old);
}
void my_flush(void)
{
	while(getchar()!='\n')
		continue;
}
struct termios *my_noecho(void)
{
	struct termios new,*old;
	old=malloc(sizeof(struct termios));
	if(tcgetattr(STDIN_FILENO,old)==-1)
		error_quit("Get Terminal info Error!");
	new=*old;
	new.c_lflag&=~ECHOFLAGSNO;
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&new)==-1)
		error_quit("Set Terminal info Error!");
	return old;
}
void my_echo(struct termios *old)
{
	tcsetattr(STDIN_FILENO,TCSAFLUSH,old);
}
struct termios *my_nonb_input(void)
{
	struct termios *old,new;
	int flag_i;
	old=malloc(sizeof(struct termios));
	if(tcgetattr(STDIN_FILENO,old)==-1)
		error_quit("Get Terminal info Error!");
	new=*old;
	new.c_lflag&=~ECHOFLAGSNONB;
	if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&new)==-1)
		error_quit("Set Terminal info Error!");
	flag_i=fcntl(STDIN_FILENO,F_GETFL);
	flag_i|=O_NONBLOCK;
	if(fcntl(STDIN_FILENO,F_SETFL,flag_i)==-1)
		error_quit("Set Input info Error!");
	return old;
}
void my_can_input(struct termios *old)
{
	int flag;
	tcsetattr(STDIN_FILENO,TCSAFLUSH,old);
	flag=fcntl(STDIN_FILENO,F_GETFL);
	flag&=O_NONBLOCK;
	if(fcntl(STDIN_FILENO,F_SETFL,flag)==-1)
		error_quit("Set Input info Error!");
}
void my_getch(char *msg)
{
	int x,y;
	initscr();
	getmaxyx(stdscr,y,x);
	mvprintw(y/2,x/2-(strlen(msg)+1)/2,"%s",msg);
	refresh();
	getch();
	endwin();
}
