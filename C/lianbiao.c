#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>

typedef struct linklist
{
        char *name;
        struct linklist *next;
}linknode, *linklistp;

linklistp insert_local(linklistp head, const  linklistp node)
{
        linklistp temp, perv;

        assert(node);

        temp = head;
        if(temp == NULL)
        {
                head = node;
                printf("creat linklist");
                return head;
         }

        if(strcmp(node->name, temp->name) < 0)
        {
                printf("insert in hea");
                node->next = temp;
                head = node;

                return head;
        }
        perv = head;
        temp = temp->next;
        while(temp)
        {
                if(strcmp(node->name, temp->name) > 0)
                {       perv = temp;
                        temp = temp->next;
                }
                else
                        break;
        }
        node->next = temp;
        perv->next  = node;
        return head;
}

void output(linklistp head)
{
        linklistp temp;

        temp = head;
        assert(temp);

        while(temp)
        {
                printf("%s  ", temp->name);
                temp = temp->next;
        }
        printf("");
}

int main(int argc, char *argv[])
{
        linklistp head=NULL, node;
        DIR *dir = NULL;
        struct dirent* dp = NULL;
        if(argc != 2)
        {
                printf("please inter dir");
                exit(EXIT_FAILURE);
        }
        dir = opendir(argv[1]);
        while((dp = readdir(dir)) != NULL)
        {
                if(dp->d_name[0] == '.')
                        continue;
                node = (linklistp)malloc(sizeof(node));
                node->next = NULL;
                node->name = (char *)malloc(sizeof(dp->d_name) + 1);
                memset(node->name,' ', sizeof(dp->d_name) + 1);
                strncpy(node->name, dp->d_name, sizeof(dp->d_name));
                head = insert_local(head, node);

                output(head);
                getchar();
        }

        //output(head);
}