#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode
{
  char data;
  struct Lnode *next;
} Lnode, *LinkList;

Lnode *create (void)
{
  Lnode *pnode;
  pnode = (Lnode *) malloc (sizeof (Lnode));
  pnode->next = NULL;
  return pnode;
}

void init (Lnode* phead)
{
  Lnode* p = phead;
  Lnode* s;
  int i=10;
  printf("－－－－－－－开始初始元素－－－－－－－－\n");
  while(i--)
    {
      s = (Lnode *) malloc (sizeof (Lnode));
      if(s == NULL)
    perror("malloc error");
      printf("请输入第%d个初始元素\n",i);
      scanf ("%c", &s->data);
      getchar();
      s->next = p->next;
      p->next = s;
    }
   printf("－－－－－－－初始元素结束－－－－－－－－\n");
}

void del (Lnode * p, int x)        //删除位置为X的元素(from 1)

{
  int i = 0;
  char e;
  Lnode *q = p;
  Lnode *t;
  while (q->next != NULL && i < x-1)
    {
      i++;
      q = q->next;        //q指向要删除的位置前一个元素

    }
  if (!(q->next) || i > x-1)
    printf ("未找到指定位置!\n");
  else
   {
      t = q->next;
      e = t->data;
      q->next = t->next;
      free (t);
      printf ("删除成功第%d个元素%c!\n",x,e);
    }
}

void get (Lnode * p, int x)        //取出位置为X的元素(from 1)

{
  int i = 0;
  char e;
  Lnode *q = p;
  while (q->next != NULL && i < x-1)
    {
      i++;
      q = q->next;        //q指向要取出的位置前一个元素

    }
  if (!(q->next) || i > x-1)
    printf ("未找到指定位置!\n");
  else
   {
      e = q->next->data;
      printf ("第%d个元素为%c!\n",x,e);
    }
}

void insert (Lnode * p, int x, char c)    //在位置X之前插入元素C,就是插入后要插入的元素位置为x

{
  int i = 0;
  Lnode *q = p;
  Lnode *t;
  while (q && i < x-1)
    {
      i++;
      q = q->next;
    }
 if(q && (i == x-1))
  {
    t = (Lnode *) malloc (sizeof (Lnode));
    t->data = c;
    t->next = q->next;
    q->next = t;
    printf ("插入成功!\n");
  }
}

void show (Lnode * q)
{
  Lnode *temp = q->next;
  int i = 1;
  while (temp != NULL)
    {
      printf ("%d->", i);
      temp = temp->next;
      i++;
    }
  printf ("NULL\n");
  temp = q->next;
  while (temp != NULL)
    {
      printf ("%c->", temp->data);
      temp = temp->next;
    }
  printf ("NULL\n");
}

Lnode * reverse (Lnode * head)
{
  Lnode *q = head->next->next;
  Lnode *temp;
  Lnode *r;
  if (head->next == NULL || q == NULL)
    {
      printf ("逆置成功!\n");
      return head;
    }
  head->next->next = NULL;
  while (q != NULL)
    {
      r = head->next;
      head->next = q;
      temp = q->next;
      q->next = r;
      q = temp;
    }
  printf ("逆置成功!\n");
  return head;
}

void quit (Lnode * head)
{
  Lnode *p = head->next;
  Lnode *q;
  while (p != NULL)
    {
      q = p;
      p = p->next;
      free (q);
    }
}

void help ()
{
  printf
    ("0 帮助信息 1 插入元素 2 删除元素 3 逆置链表 4 显示链表 5 取元素 6 退出\n");
}

int main(int argc, char *argv[])
{
  int pos, cmd;
  char ch;
  Lnode *phead = create ();
  init (phead);
  help();
  scanf ("%d", &cmd);
  while (1)
    {
      switch (cmd)
    {
    case 1:
     printf
     ("请依次输入要插入的元素位置及元素的值:\n(如果输入位置越界,则插入到链表尾部)");
     scanf ("%d%s", &pos, &ch);
     //printf("pos=%d,ch=%c",pos,ch);

     insert (phead, pos, ch);
     scanf ("%d", &cmd);
     break;
    case 2:
     printf ("请依次输入要删除的元素位置:");
     scanf ("%d", &pos);
      //printf("pos=%d",pos);

     del (phead, pos);
     scanf ("%d", &cmd);
     break;
    case 3:
     phead = reverse (phead);
     scanf ("%d", &cmd);
     break;
    case 0:
     help ();
     scanf ("%d", &cmd);
     break;
    case 4:
     show (phead);
     scanf ("%d", &cmd);
     break;
    case 5:
     printf ("请依次输入要查找的元素位置:");
     scanf ("%d", &pos);
     get (phead,pos);
     scanf ("%d", &cmd);
     break;
    case 6:
     quit (phead);
     goto exit;
    default:
     printf ("请输入正确的命令!\n");
     scanf ("%d", &cmd);
     break;
    }
    }
exit:
  printf ("链表空间已经释放,再见!\n");
  return 0;
}