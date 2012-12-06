#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define DEBUG
#ifdef DEBUG
int num=0;
#endif
void error_quit(const char *msg)
{
	printf("%s\n",msg);
	exit(1);
}
void change_to_code(FILE *fp,const char *ch)
{
	char buf;
	while(!feof(fp))
	{
		fread(&buf,sizeof(char),1,fp);
		if(buf=='\t')
#ifdef DEBUG
			++num;
#else
		{
			buf='\0';
			for(int i=0;i!=4;++i)
				printf("%s",ch);
		}
		printf("%c",buf);
#endif
	}
#ifdef DEBUG
	printf("Tab=%d\n",num);
#endif
}
void change_space(FILE *fp,const char *ch)
{
	char buf[2];
	while(!feof(fp))
	{
		fread(&buf[0],sizeof(char),1,fp);
		if(buf[0]==' ')
		{
			fread(&buf[1],sizeof(char),1,fp);
			if(buf[1]==' ')
#ifdef DEBUG
				++num;
#else
			{
				buf[0]='\0';
				buf[1]='\0';
				printf("%s",ch);
			}
#endif
		}
		else
			buf[1]='\0';
		printf("%c%c",buf[0],buf[1]);
	}
#ifdef DEBUG
	printf("num=%d\n",num);
#endif
}
void help(void)
{
	printf("change filename [code no]\n");
	printf("--cdode:\n");
	printf("\tchange to code\n");
	printf("--no:\n");
	printf("\tonly change space!\n");
	exit(1);
}
int main(int argc,char **argv)
{
	if(argc<3)
		help();
	else if(argc>3)
		error_quit("Argument Error!");
	FILE *fp;
	const char *ch="　";
	if((fp=fopen(argv[1],"rb"))==NULL)
		error_quit("Open File Error!");
	if(strcmp(argv[2],"--code")==0)
		change_to_code(fp,ch);
	else if(strcmp(argv[2],"--no")==0)
		change_space(fp,ch);
	else
		help();
	fclose(fp);
	return 0;
}
