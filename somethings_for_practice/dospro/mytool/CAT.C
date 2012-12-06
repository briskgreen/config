#include <stdio.h>
#include <stdlib.h>
void error_quit(const char *msg)
{
        printf("%s\n",msg);
        exit(1);
}
void openfile(FILE **fp,const char *filename)
{
	if((*fp=fopen(filename,"r"))==NULL)
                error_quit("Open File Error!");
}
void putfile(FILE *fp)
{
        char buf;
        while(!feof(fp))
        {
                fread(&buf,sizeof(char),1,fp);
                printf("%c",buf);
        }
}
int main(int argc,char **argv)
{
	int i=1;
	FILE *fp;
	if(argc<2)
                error_quit("No File Can Read!");
        while(argv[i]!=NULL)
        {
		openfile(&fp,argv[i]);
		putfile(fp);
                fclose(fp);
                ++i;
        }
        return 0;
}
