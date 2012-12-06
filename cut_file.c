#include <stdio.h>
#include <stdlib.h>
void error_quit(const char *msg)
{
	printf("Error:%s\n",msg);
	exit(1);
}
void cut_file(const char *from_file,const char *to_file)
{
	FILE *in,*out;
	if(((in=fopen(from_file,"rb"))!=NULL)&&((out=fopen(to_file,"wb"))!=NULL))
	{
		long file_len;
		fseek(in,0L,SEEK_END);
		file_len=ftell(in);
		rewind(in);
		file_len/=2;
		//fseek(in,file_len,SEEK_CUR);
		char temp;
		while(file_len--)
		{
			fread(&temp,sizeof(char),1,in);
			fwrite(&temp,sizeof(char),1,out);
		}
		fclose(in);
		fclose(out);
	}
	else
		error_quit("Open File Error!");
}
int main(int argc,char **argv)
{
	if(argc!=3)
		error_quit("Arugment Error!");
	cut_file(argv[1],argv[2]);
	printf("Cut File OK\n");
	return 0;
}
