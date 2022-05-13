#include "md5.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define READ_DATA_SIZE	1024
#define MD5_SIZE		16
#define MD5_STR_LEN		(MD5_SIZE * 2)

struct FILE_INFO;
// function declare
int Compute_string_md5(unsigned char *dest_str, unsigned int dest_len, char *md5_str);
int Compute_file_md5(const char *file_path, char *md5_str);

void* md5thread(void* args);
void* sha256thread(void* args);
void threadstart(char *fangshi,char *filepath,char *savepath);
void zhaiyao(char *fangshi,char *path,char *name,char *savepath);
void List(char *fangshi,char *path,char *savepath);

 
int main(int argc, char *argv[]){

    int ch;
    //opterr = 0;
    char *fangshi;
    char *savepath;
	
    while((ch = getopt(argc,argv,"f:o:d:l:"))!= -1)
    {
        switch(ch)
        {
            case 'f':
                fangshi=optarg;
                break;
            case 'o':
            printf("%s",optarg);
                savepath=optarg;
                //打印time
                char *date=(char *)malloc(sizeof(savepath)+34);
                sprintf(date,"date >> %sconfig.txt",savepath);
                printf("开始时间：%s\n",date);
                system(date);
                free(date);
                break;
            case 'd': 
                printf("摘要目录:%s\n",optarg);
                printf("保存地址%s\n",savepath);
                //m时md5，s时sha256，a是全部
                List(fangshi,optarg,savepath);
                break;
            case 'l': 
                printf("摘要文件:%s\n",optarg);
                printf("保存地址%s\n",savepath);
                threadstart(fangshi,optarg,savepath);
                break;
            default: 
                printf("错误\n");
        }
    }
    printf("程序结束\n");
    return 0;
}

struct FILE_INFO{
    char *filenpath,*savepath;
};

/**
 * compute the value of a file
 * @param  file_path
 * @param  md5_str
 * @return 0: ok, -1: fail
 */
int Compute_file_md5(const char *file_path, char *md5_str)
{
	int i;
	int fd;
	int ret;
	unsigned char data[READ_DATA_SIZE];
	unsigned char md5_value[MD5_SIZE];
	MD5_CTX md5;

	fd = open(file_path, O_RDONLY);
	if (-1 == fd)
	{
		perror("open");
		return -1;
	}

	// init md5
	MD5Init(&md5);

	while (1)
	{
		ret = read(fd, data, READ_DATA_SIZE);
		if (-1 == ret)
		{
			perror("read");
			close(fd);
			return -1;
		}

		MD5Update(&md5, data, ret);

		if (0 == ret || ret < READ_DATA_SIZE)
		{
			break;
		}
	}

	close(fd);

	MD5Final(&md5, md5_value);

	// convert md5 value to md5 string
	for(i = 0; i < MD5_SIZE; i++)
	{
		snprintf(md5_str + i*2, 2+1, "%02x", md5_value[i]);
	}

	return 0;
}

/**
 * MD5 thread
 * @param FILE_INFO
 */

void* md5thread(void* args){

    int ret;
	char md5_str[MD5_STR_LEN + 1];

    printf("计算MD5线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    /* char *md5shell=(char *)malloc(sizeof(fileinfo->filenpath)+sizeof(fileinfo->savepath)+1024);
    printf("打印MD5shell长度:%ld\n",sizeof(md5shell));


    sprintf(md5shell,"md5sum %s >> %sconfig.txt",fileinfo->filenpath,fileinfo->savepath);
    printf("打印MD5shell:%s\n执行shell:\n",md5shell);

    system(md5shell);
    free(md5shell); */

    // test file md5
	ret = Compute_file_md5(fileinfo->filenpath, md5_str);
    printf("MD函数filepath:%s\n",fileinfo->filenpath);
	if (0 == ret)
	{
		printf("[file - %s] md5 value:\n", fileinfo->filenpath);
		printf("%s\n", md5_str);
	}

    printf("计算MD5线程结束\n");

    return NULL;
}

/**
 * SHA256 thread
 * @param FILE_INFO
 */

void* sha256thread(void* args){
    printf("计算SHA256线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    char *sha256shell=(char *)malloc(sizeof(fileinfo->filenpath)+sizeof(fileinfo->savepath)+1024);
    printf("打印SHA256shell长度:%ld\n",sizeof(sha256shell));


    sprintf(sha256shell,"sha256sum %s >> %sconfig.txt",fileinfo->filenpath,fileinfo->savepath);
    printf("打印SHA256shell:%s\n执行shell:\n",sha256shell);

    system(sha256shell);
    free(sha256shell);
    printf("计算SHA256线程结束\n");
    return NULL;
}

/**
 * start thread
 * @param fangshi
 * @param filepath
 * @param savepath
 */

void threadstart(char *fangshi,char *filepath,char *savepath){
    if (strcmp(fangshi, "a") == 0)
    {
        printf("多线程开始\n");
        pthread_t md5,sha256;

        struct FILE_INFO fileinfo;
        fileinfo.filenpath=filepath;
        fileinfo.savepath=savepath;
        printf("摘要fileinfo.filepath=%s\n",fileinfo.filenpath);
        printf("摘要fileinfo.savepath=%s\n",fileinfo.savepath);
        pthread_create(&md5,NULL,md5thread,&fileinfo);
        pthread_create(&sha256,NULL,sha256thread,&fileinfo);
        pthread_join(md5,NULL);
        pthread_join(sha256,NULL);
        printf("多线程结束\n");
    }else if (strcmp(fangshi, "m") == 0)
    {
         printf("计算MD5线程开始\n");
    
        
        /* printf("单线程fileinfo.filepath=%s\n",filepath);
        printf("单线程fileinfo.savepath=%s\n",savepath);

        char *md5shell=(char *)malloc(sizeof(filepath)+sizeof(savepath)+1024);
        printf("打印MD5shell长度:%ld\n",sizeof(md5shell));

        sprintf(md5shell,"md5sum %s >> %s/config.txt",filepath,savepath);
        printf("打印MD5shell:%s\n执行shell:\n",md5shell);

        system(md5shell);
        free(md5shell);
        printf("计算MD5线程结束\n"); */
        int ret;
        char md5_str[MD5_STR_LEN + 1];

        printf("计算MD5线程开始\n");
        
        ret = Compute_file_md5(filepath, md5_str);
        printf("MD函数filepath:%s\n",filepath);
        if (0 == ret)
        {
            printf("[file - %s] md5 value:\n", filepath);
            printf("%s\n", md5_str);
        }

        printf("计算MD5线程结束\n");
        
    }else if (strcmp(fangshi, "s") == 0)
    {
        printf("计算SHA256线程开始\n");
        
        printf("多线程fileinfo.filepath=%s\n",filepath);
        printf("多线程fileinfo.savepath=%s\n",savepath);
        
        char *sha256shell=(char *)malloc(sizeof(filepath)+sizeof(savepath)+1024);
        printf("打印SHA256shell长度:%ld\n",sizeof(sha256shell));

        sprintf(sha256shell,"sha256sum %s >> %sconfig.txt",filepath,savepath);
        printf("打印SHA256shell:%s\n执行shell:\n",sha256shell);

        system(sha256shell);
        free(sha256shell);
        printf("计算SHA256线程结束\n");
    } 

}

/**
 * zhiyao 文件路径拼接
 * @param fangshi
 * @param path
 * @param name
 * @param savepath
 */

void zhaiyao(char *fangshi,char *path,char *name,char *savepath){

    printf("摘要开始：");
    

    char *FILEPATH=(char *)malloc(sizeof(path)+sizeof(name)+1024);
    strcpy(FILEPATH,path);
    strcat(FILEPATH,name);
    printf("文件绝对路径：%s\n",FILEPATH);

    threadstart(fangshi,FILEPATH,savepath);
    
    free(FILEPATH);
    printf("摘要结束：\n");
}

/**
 * 遍历文件及目录
 * @param fangshi
 * @param path
 * @param savepath
 */

void List(char *fangshi,char *path,char *savepath){   
    printf("遍历目录\n");
    char *FILELIST;
    struct dirent* ent = NULL;
    DIR *pDir;
    pDir=opendir(path);
    //d_reclen：16表示子目录或以.开头的隐藏文件，24表示普通文本文件,28为二进制文件，还有其他……
    while (NULL != (ent=readdir(pDir)))
    {
        //printf("reclen=%d    type=%d\t", ent->d_reclen, ent->d_type);
        printf("%s\n",ent->d_name);
        if (ent->d_type==8)
        {
            //printf("文件路径：%s\n文件名称：%s\n保存配置路径：%s\n",path,ent->d_name,savepath);
            zhaiyao(fangshi,path,ent->d_name,savepath);
        }
        else if(ent->d_type==4)
        {
            if(strcmp(ent->d_name,"..")==0 || strcmp(ent->d_name,".")==0) {
                printf("[.]或者[..]的目录[%s]\n",ent->d_name);
            }
            else{
                printf("目录[%s]\n\n", ent->d_name);
                FILELIST=(char *)malloc(sizeof(path)+sizeof(ent->d_name)+40);
                sprintf(FILELIST,"%s%s/",path,ent->d_name);
                printf("目录递归%s\n",FILELIST);
                List(fangshi,FILELIST,savepath);
                printf("目录递归%s结束\n",FILELIST);
                free(FILELIST);
            }
                
        }
    }
    printf("List遍历结束\n");
}
