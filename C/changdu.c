#include <sys/stat.h>   
#include <unistd.h>   
#include <stdio.h>   
/* 
    函数名：getFileSize(char * strFileName)  
    功能：获取指定文件的大小 
    参数： 
        strFileName (char *)：文件名 
    返回值： 
        size (int)：文件大小 
 */  
int getFileSize(char * strFileName)   
{  
    FILE * fp = fopen(strFileName, "r");  
    fseek(fp, 0L, SEEK_END);  
    int size = ftell(fp);  
    fclose(fp);  
    return size;  
}  
/* 
    函数名：getFileSizeSystemCall(char * strFileName)    
    功能：获取指定文件的大小 
    参数： 
        strFileName (char *)：文件名 
    返回值： 
        size (int)：文件大小 
 */  
int getFileSizeSystemCall(char * strFileName)   
{  
    struct stat temp;  
    stat(strFileName, &temp);  
    return temp.st_size;  
}  
int main()  
{  
    printf("size = %d/n", getFileSize("bianli.c"));  
    printf("size = %d/n", getFileSizeSystemCall("bianli.c"));  
    return 0;  
} 
