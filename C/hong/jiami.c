#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct FILE_INFO{
    char *name,*filenpath,*savepath;
};
/*
创建链表，用来保存文件路径
以下是对链表的操作
*/
typedef struct Lnode
{
    char *data;
    char *name;
    struct Lnode *next;
} Lnode, *LinkList;

Lnode *create (void)
{
    Lnode *pnode;
    pnode = (Lnode *) malloc (sizeof (Lnode));
    pnode->next = NULL;
    return pnode;
}

int add(Lnode* phead,char *path,char *name){
    Lnode* p = phead;
    Lnode* s;
    int sum=0;
    s = (Lnode *) malloc (sizeof (Lnode));
    char *FILEPATH=(char *)malloc(1024);
    char *NAME=(char *)malloc(1024);
    strcpy(FILEPATH,path);
    strcpy(NAME,name);
    if(s == NULL)
        perror("malloc error");
    s->data=FILEPATH;
    s->name=NAME;
    while(p->next!=NULL){
        p=p->next;
        sum++;
    }
    p->next=s;
    s->next=NULL;
    sum++;
    printf("%s\n",s->data);
    return sum;
}

int getnum(Lnode* phead){
    Lnode* p = phead;
    int sum=0;
    while(p->next!=NULL){
        p=p->next;
        sum++;
    }
    return sum;
}

void show(Lnode *q){
    int i=1;
    Lnode *temp = q->next;
    temp = q->next;
    while (temp != NULL){
        printf ("第%d个路径%s\n",i,temp->data);
        printf ("第%d个名称%s\n",i,temp->name);
        temp = temp->next;
        i++;
    }
}

char* getpath(Lnode *q,int num){
    int i=1;
    char *path;
    Lnode *temp = q->next;
    temp = q->next;
    while (i<num){
        temp = temp->next;
        i++;
    }
    printf("num:%d第%d个数据%s\n",num,i,temp->data);
    printf("num:%d第%d个名称%s\n",num,i,temp->name);
    return temp->data;
}

char* getname(Lnode *q,int num){
    int i=1;
    char *path;
    Lnode *temp = q->next;
    temp = q->next;
    while (i<num){
        temp = temp->next;
        i++;
    }
    printf("num:%d第%d个数据%s\n",num,i,temp->data);
    printf("num:%d第%d个名称%s\n",num,i,temp->name);
    return temp->name;
}

void quit (Lnode * head)
{
    Lnode *p = head->next;
    Lnode *q;
    while (p != NULL){
        q = p;
        p = p->next;
        free(q->data);
        free(q);
    }
}
//aes加密线程
void* encaesthread(void* args){
    printf("计算MD5线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    char *md5shell=(char *)malloc(1024);
    printf("打印MD5shell长度:%ld\n",sizeof(md5shell));


    sprintf(md5shell,"openssl enc -e -aes-128-cbc -a -iter 100 -pbkdf2  -k 123456 -in %s -out %s%s.enc",fileinfo->filenpath,fileinfo->savepath,fileinfo->name);
    printf("打印MD5shell:%s\n执行shell:\n",md5shell);

    system(md5shell);
    free(md5shell);
    printf("计算MD5线程结束\n");
    return NULL;
}
//aes解密线程
void* decaesthread(void* args){
    printf("计算MD5线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    char *md5shell=(char *)malloc(1024);
    printf("打印MD5shell长度:%ld\n",sizeof(md5shell));


    sprintf(md5shell,"openssl enc -d -aes-128-cbc -a -iter 100 -pbkdf2  -k 123456 -in %s -out %s%s.dec",fileinfo->filenpath,fileinfo->savepath,fileinfo->name);
    printf("打印MD5shell:%s\n执行shell:\n",md5shell);

    system(md5shell);
    free(md5shell);
    printf("计算MD5线程结束\n");
    return NULL;
}
//des加密线程
void* encdesthread(void* args){
    printf("计算SHA256线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    char *sha256shell=(char *)malloc(1024);
    printf("打印SHA256shell长度:%ld\n",sizeof(sha256shell));


    sprintf(sha256shell,"openssl enc -e -des-cbc -a -iter 100 -pbkdf2  -k 123456 -in %s -out %s%s.enc",fileinfo->filenpath,fileinfo->savepath,fileinfo->name);
    printf("打印SHA256shell:%s\n执行shell:\n",sha256shell);

    system(sha256shell);
    free(sha256shell);
    printf("计算SHA256线程结束\n");
    return NULL;
}
//des解密线程
void* decdesthread(void* args){
    printf("计算SHA256线程开始\n");
    
    struct FILE_INFO *fileinfo;
    fileinfo=(struct FILE_INFO *)args;
    
    printf("多线程fileinfo.filepath=%s\n",fileinfo->filenpath);
    printf("多线程fileinfo.savepath=%s\n",fileinfo->savepath);
    

    char *sha256shell=(char *)malloc(1024);
    printf("打印SHA256shell长度:%ld\n",sizeof(sha256shell));


    sprintf(sha256shell,"openssl enc -d -des-cbc -a -iter 100 -pbkdf2  -k 123456 -in %s -out %s%s.dec",fileinfo->filenpath,fileinfo->savepath,fileinfo->name);
    printf("打印SHA256shell:%s\n执行shell:\n",sha256shell);

    system(sha256shell);
    free(sha256shell);
    printf("计算SHA256线程结束\n");
    return NULL;
}
//加密多线程
void encthreadassign(char *fangshi,Lnode * head,char *savepath,int start,int space){
    pthread_t aescbc[space];
    pthread_t descbc[space];
    struct FILE_INFO fileinfo[space];
    int n=0;
    printf("方式：%s\n",fangshi);
    if (strcmp(fangshi, "a") == 0)
    {
        printf("计算加密aescbc线程开始\n");
        printf("多线程赋值\n");
        for(;n<space;n++){
            fileinfo[n].filenpath=getpath(head,start+n);
            fileinfo[n].name=getname(head,start+n);
            fileinfo[n].savepath=savepath;
            printf("摘要fileinfo.filepath=%s\n",fileinfo[n].filenpath);
            printf("摘要fileinfo.savepath=%s\n",fileinfo[n].savepath);
        }
        n=0;
        printf("多线程执行\n");
        for(;n<space;n++){
            pthread_create(&aescbc[n],NULL,encaesthread,&fileinfo[n]);
        }
        n=0;
        printf("多线程等待完成");
        for(;n<space;n++){
            pthread_join(aescbc[n],NULL);
        }
        printf("计算加密aescbc线程结束\n");
    }else if (strcmp(fangshi, "d") == 0)
    {
        printf("计算加密des线程开始\n");
        printf("多线程赋值\n");
        for(;n<space;n++){
            fileinfo[n].filenpath=getpath(head,start+n);
            fileinfo[n].name=getname(head,start+n);
            fileinfo[n].savepath=savepath;
            printf("摘要fileinfo.filepath=%s\n",fileinfo[n].filenpath);
            printf("摘要fileinfo.savepath=%s\n",fileinfo[n].savepath);
        }
        n=0;
        printf("多线程执行\n");
        for(;n<space;n++){
            pthread_create(&descbc[n],NULL,encdesthread,&fileinfo[n]);
        }
        n=0;
        printf("多线程等待完成");
        for(;n<space;n++){
            pthread_join(descbc[n],NULL);
        }
        printf("计算加密des线程结束\n");
    } 
}
//解密多线程
void decthreadassign(char *fangshi,Lnode * head,char *savepath,int start,int space){
    pthread_t aescbc[space];
    pthread_t descbc[space];
    struct FILE_INFO fileinfo[space];
    int n=0;
    printf("方式：%s\n",fangshi);
    if (strcmp(fangshi, "a") == 0)
    {
        printf("计算解密aescbc线程开始\n");
        printf("多线程赋值\n");
        for(;n<space;n++){
            fileinfo[n].filenpath=getpath(head,start+n);
            fileinfo[n].name=getname(head,start+n);
            fileinfo[n].savepath=savepath;
            printf("摘要fileinfo.filepath=%s\n",fileinfo[n].filenpath);
            printf("摘要fileinfo.savepath=%s\n",fileinfo[n].savepath);
        }
        n=0;
        printf("多线程执行\n");
        for(;n<space;n++){
            pthread_create(&aescbc[n],NULL,decaesthread,&fileinfo[n]);
        }
        n=0;
        printf("多线程等待完成");
        for(;n<space;n++){
            pthread_join(aescbc[n],NULL);
        }
        printf("计算解密aescbc线程结束\n");
    }else if (strcmp(fangshi, "d") == 0)
    {
        printf("计算解密descbc线程开始\n");
        printf("多线程赋值\n");
        for(;n<space;n++){
            fileinfo[n].filenpath=getpath(head,start+n);
            fileinfo[n].name=getname(head,start+n);
            fileinfo[n].savepath=savepath;
            printf("摘要fileinfo.filepath=%s\n",fileinfo[n].filenpath);
            printf("摘要fileinfo.savepath=%s\n",fileinfo[n].savepath);
        }
        n=0;
        printf("多线程执行\n");
        for(;n<space;n++){
            pthread_create(&descbc[n],NULL,decdesthread,&fileinfo[n]);
        }
        n=0;
        printf("多线程等待完成");
        for(;n<space;n++){
            pthread_join(descbc[n],NULL);
        }
        printf("计算解密descbc线程结束\n");
    } 
}


void threadstart(char *fangshi,Lnode *head,char *savepath,int space,int encordec){
    printf("多线程开始\n");
    int sum=getnum(head);
    printf("多线程sum:%d\n",sum);
    int n=0;
    int m=space;
    printf("assign\n");
    if (encordec==1)
    {
        //加密
        while(sum-m>0){
            encthreadassign(fangshi,head,savepath,n,space);
            n=n+space;
            m=m+space;
        }
        if(sum>m-space){
            encthreadassign(fangshi,head,savepath,n,sum-m+space);
        }

    }else if (encordec==2)
    {
        //解密
        while(sum-m>0){
            decthreadassign(fangshi,head,savepath,n,space);
            n=n+space;
            m=m+space;
        }
        if(sum>m-space){
            decthreadassign(fangshi,head,savepath,n,sum-m+space);
        }
    }
    

    
    printf("多线程结束\n");
}

/*
将文件路径加入到链表中
*/
void zhaiyao(char *path,char *name,Lnode *head){

    //printf("摘要开始：");
    int i;

    char *FILEPATH=(char *)malloc(1024);
    strcpy(FILEPATH,path);
    strcat(FILEPATH,name);
    printf("文件绝对路径：%s\n",FILEPATH);
    i=add(head,FILEPATH,name);
    printf("第%d个数据\n",i);
    printf("函数返回值:%s\n",getpath(head,i));
    printf("函数返回值:%s\n",getname(head,i));
    //printf("pop第%s个数据\n",pop(head,i));
    
    //threadstart(fangshi,FILEPATH,savepath);
    
    free(FILEPATH);
    printf("摘要结束：\n");
}

void List(char *fangshi,char *path,char *savepath,int thread,int decorenc){   
    printf("遍历目录\n");
    Lnode *phead = create();
    char *FILELIST;
    struct dirent* ent = NULL;
    DIR *pDir;
    pDir=opendir(path);
    //d_reclen：16表示子目录或以.开头的隐藏文件，24表示普通文本文件,28为二进制文件，还有其他……
    while (NULL != (ent=readdir(pDir)))
    {
        //printf("reclen=%d    type=%d\t", ent->d_reclen, ent->d_type);
        //printf("%s\n",ent->d_name);
        if (ent->d_type==8)
        {
            //printf("文件路径：%s\n文件名称：%s\n保存配置路径：%s\n",path,ent->d_name,savepath);
            //
            zhaiyao(path,ent->d_name,phead);
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
                List(fangshi,FILELIST,savepath,thread,decorenc);
                printf("目录递归%s结束\n",FILELIST);
                free(FILELIST);
            } 

                
        }
    }
    
    printf("show\n");
    show(phead);
    threadstart(fangshi,phead,savepath,thread,decorenc);
    printf("List遍历结束\n");
    quit(phead);
}


 
int main(int argc, char *argv[]){

    int thread=10;
    int ch;
    int encordec=0;
    //opterr = 0;
    char *fangshi="a";
    int pathorfile=0;
    char *filename=(char *)malloc(64);
    char *path=(char *)malloc(1024);
    char *savepath=(char *)malloc(1024);
	
    while((ch = getopt(argc,argv,"k:f:o:d:l:se"))!= -1)
    {
        switch(ch)
        {
            case 'k':
                thread=atoi(optarg);
                printf("线程数:%d",thread);
                break;
            case 'f':
                //m时md5，s时sha256，a是全部
                //aescbc:a;deccbc:d
                fangshi=optarg;
                printf("方式:%s\n",fangshi);
                break;
            case 'o':
                savepath=optarg;
                printf("保存地址%s\n",savepath);
                break;
            case 'd': 
                path=optarg;
                printf("摘要目录:%s\n",path);
                break;
            case 'l': 
                pathorfile=1;
                path=optarg;
                printf("摘要文件:%s\n",path);
                break;
            case 'e': 
                //加密
                encordec=1;
                break;
            case 's':
                //解密
                encordec=2;
                break;
            default: 
                printf("help\n");
                printf("k 线程数(默认10)\n");
                printf("f 方式(m:md5,s:sha256,a:md5&sha256)\n");
                printf("o 配置文件保存目录\n");
                printf("d 摘要目录\n");
                printf("l 摘要文件\n");
                return 0;
        }
    }
/*     //打印time
    char *date=(char *)malloc(sizeof(savepath)+34);
    sprintf(date,"date >> %sconfig.txt",savepath);
    printf("开始时间：%s\n",date);
    system(date);
    free(date); */

    if(pathorfile==0){
        List(fangshi,path,savepath,thread,encordec);
    }else{
        printf("对文件进行操作\n");
        if (strcmp(fangshi, "a") == 0)
        {
            printf("fileinfo.filepath=%s\n",path);
            printf("fileinfo.savepath=%s\n",savepath);          
            char *md5shell=(char *)malloc(1024);
            char *sha256shell=(char *)malloc(1024);
            sprintf(md5shell,"md5sum %s >> %sconfig.txt",path,savepath);
            sprintf(sha256shell,"sha256sum %s >> %sconfig.txt",path,savepath);
            printf("打印MD5shell:%s\n执行shell:\n",md5shell);
            printf("打印SHA256shell:%s\n执行shell:\n",sha256shell);
            system(md5shell);
            system(sha256shell);
            free(md5shell);
            free(sha256shell);
            printf("计算MD5结束\n");
            printf("计算SHA256结束\n");
        }else if (strcmp(fangshi, "m") == 0)
        {
            printf("fileinfo.filepath=%s\n",path);
            printf("fileinfo.savepath=%s\n",savepath);          
            char *md5shell=(char *)malloc(1024);
            sprintf(md5shell,"md5sum %s >> %sconfig.txt",path,savepath);
            printf("打印MD5shell:%s\n执行shell:\n",md5shell);
            system(md5shell);
            free(md5shell);
            printf("计算MD5结束\n");
        }else if (strcmp(fangshi, "s") == 0)
        {
            printf("fileinfo.filepath=%s\n",path);
            printf("fileinfo.savepath=%s\n",savepath);   
            char *sha256shell=(char *)malloc(1024);
            sprintf(sha256shell,"sha256sum %s >> %sconfig.txt",path,savepath);
            printf("打印SHA256shell:%s\n执行shell:\n",sha256shell);
            system(sha256shell);
            free(sha256shell);
            printf("计算SHA256结束\n");
        }
    }

    printf("程序结束\n");
    return 0;
}
