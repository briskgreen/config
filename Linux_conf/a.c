#include "stdio.h"
#include "stdlib.h"
struct node
{int num;
 char name[10];
 char phone[12];
 struct node *next;
};
typedef struct node LINK;
#define MAL (LINK *)malloc(sizeof(LINK))
LINK *creat_link()
{LINK *head,*s,*r;
  r=head=MAL;
  s=MAL;
  scanf("%d%s%s",&s->num,s->name,s->phone);
  while(1)
   {r->next=s;
     r=s;
     s=MAL;
     scanf("%d",&s->num);
     if(s->num==-1)
         break;
     else
         scanf("%s%s",s->name,s->phone);
   }
  r->next=NULL;
  return head;
}
void print_link(LINK *head)
{if(head->next==NULL)
      printf("LINK is NULL!");
  else
      for(head=head->next;head!=NULL;head=head->next)
              printf("No.%d:%s %s\n",head->num,head->name,head->phone);
}
void output_file(LINK *head)
{FILE *open;
if((open=fopen("Z:/a.txt","w+"))==NULL)
   {printf("加载失败!");
     getchar();
     exit(1);
   }
 for(head=head->next;head->next!=0;head=head->next)
         fwrite(head,sizeof(head),1,open);
 fclose(open);
}
LINK *read_file()
{LINK *head,*s,*r;
  FILE *open;
  if((open=fopen("Z:/a.txt","r"))==NULL)
    {printf("加载失败!");
      setbuf(stdin,NULL);
      getchar();
      exit(1);
    }
  head=r=MAL;
  while(!feof(open))
    {s=MAL;
      fread(s,sizeof(s),1,open);
      r->next=s;
      r=s;
    }
  fclose(open);
  return head;
}
void main()
{LINK *head;
  head=creat_link();
  print_link(head);
  output_file(head);
  head=read_file();
  print_link(head);
}
