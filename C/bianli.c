#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>

struct FILE_INFO{
    char *filenpath,*savepath;
};

void* md5thread(void* args){
    printf("计算MD5线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    char *md5shell=(char *)malloc(sizeof(fileinfo->filenpath)+sizeof(fileinfo->savepath)+1024);
    printf("打印MD5shell长度:%ld\n",sizeof(md5shell));


    sprintf(md5shell,"md5sum %s >> %sconfig.txt",fileinfo->filenpath,fileinfo->savepath);
    printf("打印MD5shell:%s\n执行shell:\n",md5shell);

    system(md5shell);
    free(md5shell);
    printf("计算MD5线程结束\n");
    return NULL;
}

void* sha256thread(void* args){
    printf("计算SHA256线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    char *md5shell=(char *)malloc(sizeof(fileinfo->filenpath)+sizeof(fileinfo->savepath)+1024);
    printf("打印SHA256shell长度:%ld\n",sizeof(md5shell));


    sprintf(md5shell,"sha256sum %s >> %sconfig.txt",fileinfo->filenpath,fileinfo->savepath);
    printf("打印SHA256shell:%s\n执行shell:\n",md5shell);

    system(md5shell);
    free(md5shell);
    printf("计算SHA256线程结束\n");
    return NULL;
}


void zhaiyao(char *path,char *name,char *savepath){

    printf("摘要开始：");
    pthread_t md5,sha256;

    char *FILEPATH=(char *)malloc(sizeof(path)+sizeof(name)+1024);
    strcpy(FILEPATH,path);
    strcat(FILEPATH,name);
    printf("文件绝对路径：%s\n",FILEPATH);

    struct FILE_INFO fileinfo;
    fileinfo.filenpath=FILEPATH;
    fileinfo.savepath=savepath;
    printf("摘要fileinfo.filepath=%s\n",fileinfo.filenpath);
    printf("摘要fileinfo.savepath=%s\n",fileinfo.savepath);

    pthread_create(&md5,NULL,md5thread,&fileinfo);
    pthread_create(&sha256,NULL,sha256thread,&fileinfo);
    pthread_join(md5,NULL);
    pthread_join(sha256,NULL);
    
    free(FILEPATH);
    printf("摘要结束：\n");
}

void List(char *path,char *savepath)
{   
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
            zhaiyao(path,ent->d_name,savepath);
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
                List(FILELIST,savepath);
                printf("目录递归%s结束\n",FILELIST);
                free(FILELIST);
            }
                
        }
    }
    printf("List遍历结束\n");
}


 
int main(int argc, char *argv[]){

	//打印time
    char *date=(char *)malloc(sizeof(argv[2])+34);
    sprintf(date,"date >> %sconfig.txt",argv[2]);
    printf("开始时间：%s\n",date);
    system(date);
    free(date);

    printf("遍历目录:%s\n",argv[1]);
    printf("保存地址%s\n",argv[2]);

    List(argv[1],argv[2]);

    printf("程序结束\n");

    return 0;
}
