#include<stdio.h>
#include<unistd.h>
int main(int argc,char **argv)
{
    int ch;
    opterr = 0;
    while((ch = getopt(argc,argv,"r:l:"))!= -1)
    {
        switch(ch)
        {
            case 'r': 
                printf("摘要目录:%s\n",argv[2]);
                printf("保存地址%s\n",argv[3]);
                break;
            case 'l': 
                printf("摘要文件:%s\n",argv[2]);
                printf("保存地址%s\n",argv[3]);
                break;
            default: 
                printf("错误\n");
        }
    }
    return 0;
}