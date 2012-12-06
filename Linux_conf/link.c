#include "stdio.h"
#include "stdlib.h"
struct node
{int data;
 char name[10];
 struct node *next;
};
typedef struct node LINK;
#define MAL (LINK *)malloc(sizeof(LINK))
LINK *creat_link()
{LINK *head,*s,*r;
 r=head=MAL;
 s=MAL;
 printf("Please input data and name:");
 scanf("%d%s",&s->data,s->name);
 while(1)
   {r->next=s;
   r=s;
   s=MAL;
   printf("Please input data and name:");
   setbuf(stdin,NULL);
   scanf("%d",&s->data);
   if(s->data==-1)
      break;
   setbuf(stdin,NULL);
   scanf("%s",s->name);
  }
 r->next=0;
 return head;
}
void print_link(LINK *head)
{
   if(head->next==0)
      printf("Link is NULL!");
   else
      for(head=head->next;head!=0;head=head->next)
          printf("%d %s\n",head->data,head->name);
}
LINK *sort_link(LINK *head)
{LINK *q,*p,*temp;
  for(q=head;q->next!=0;q=q->next)
          for(p=q->next;p->next!=0;p=p->next)
                  if(q->next->data>p->next->data)
                   {if(q->next==p)
                      {temp=p->next;
                        p->next=p->next->next;
                        temp->next=p;
                        q->next=temp;
                        p=temp;
                      }
                    else
                      {temp=p->next;
                        p->next=q->next;
                        q->next=temp;
                        temp=p->next->next;
                        p->next->next=q->next->next;
                        q->next->next=temp;
                      }
                   }
 return head;
}
main()
{LINK *head;
 head=creat_link();
 print_link(head);
 head=sort_link(head);
 printf("\n");
 print_link(head);
 printf("Press any key to exit. . .");
 setbuf(stdin,NULL);
 getchar();
}
