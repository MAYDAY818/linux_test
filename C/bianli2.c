#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
void List(char *path)
{
     struct dirent* ent = NULL;
     
     DIR *pDir;
     pDir=opendir(path);
     //d_reclen：16表示子目录或以.开头的隐藏文件，24表示普通文本文件,28为二进制文件，还有其他……
     while (NULL != (ent=readdir(pDir)))
     {
         printf("reclen=%d    type=%d\t", ent->d_reclen, ent->d_type);
         if (ent->d_type==8)
         {   
            printf("普通文件[%s]\n", ent->d_name);
            
         }
         
         else if(ent->d_type==4)
         {
            if(strcmp(ent->d_name,"..")==0 || strcmp(ent->d_name,".")==0) {
                printf("[.]开头的子目录或隐藏文件[%s]\n",ent->d_name);
                printf("1111111\n");
            }
            else
                printf("目录[%s]\n", ent->d_name);
         }
     }
}
int main(int argc, char *argv[])
{
      List(argv[1]);
      return 0;
}