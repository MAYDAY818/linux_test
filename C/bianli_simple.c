#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct FILE_INFO{
    char *filenpath,*savepath;
};

void* md5thread(void* args){
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    char *md5shell=(char *)malloc(sizeof(fileinfo->filenpath)+sizeof(fileinfo->savepath)+1024);
    sprintf(md5shell,"md5sum %s >> %sconfig.txt",fileinfo->filenpath,fileinfo->savepath);
    system(md5shell);
    free(md5shell);
    return NULL;
}

void* sha256thread(void* args){
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    char *md5shell=(char *)malloc(sizeof(fileinfo->filenpath)+sizeof(fileinfo->savepath)+1024);
    sprintf(md5shell,"sha256sum %s >> %sconfig.txt",fileinfo->filenpath,fileinfo->savepath);
    system(md5shell);
    free(md5shell);
    return NULL;
}

void threadstart(char *filepath,char *savepath){
    pthread_t md5,sha256;
    struct FILE_INFO fileinfo;
    fileinfo.filenpath=filepath;
    fileinfo.savepath=savepath;
    pthread_create(&md5,NULL,md5thread,&fileinfo);
    pthread_create(&sha256,NULL,sha256thread,&fileinfo);
    pthread_join(md5,NULL);
    pthread_join(sha256,NULL);
}
void zhaiyao(char *path,char *name,char *savepath){
    char *FILEPATH=(char *)malloc(sizeof(path)+sizeof(name)+1024);
    strcpy(FILEPATH,path);
    strcat(FILEPATH,name);
    threadstart(FILEPATH,savepath);
    free(FILEPATH);
}
void List(char *path,char *savepath)
{   
    char *FILELIST;
    struct dirent* ent = NULL;
    DIR *pDir;
    pDir=opendir(path);
    while (NULL != (ent=readdir(pDir)))
    {
        printf("%s\n",ent->d_name);
        if (ent->d_type==8)
        {
            zhaiyao(path,ent->d_name,savepath);
        }
        else if(ent->d_type==4)
        {
            if(strcmp(ent->d_name,"..")==0 || strcmp(ent->d_name,".")==0) {
            }
            else{
                FILELIST=(char *)malloc(sizeof(path)+sizeof(ent->d_name)+40);
                sprintf(FILELIST,"%s%s/",path,ent->d_name);
                List(FILELIST,savepath);
                free(FILELIST);
            }
                
        }
    }
}
int main(int argc, char *argv[]){
    char *date=(char *)malloc(sizeof(argv[3])+34);
    sprintf(date,"date >> %sconfig.txt",argv[3]);
    system(date);
    free(date);
    int ch;
    opterr = 0;
    while((ch = getopt(argc,argv,"r:l:"))!= -1)
    {
        switch(ch)
        {
            case 'r': 
                List(argv[2],argv[3]);
                break;
            case 'l': 
                threadstart(argv[2],argv[3]);
                break;
            default: 
                printf("错误\n");
        }
    }
    return 0;
}
