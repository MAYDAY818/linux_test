#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
//宏定义 分别为 赛道长度 馬数目 最小单步 最大单步
#define LENGTH 60
#define HORSENUM 6
#define MINSTEP 1
#define MAXSTEP 10
void play(int s[])
{   
    int i,j;
    int rank=1;//名次循环使用的，中途记录名次，并初始化为1
    int dis[HORSENUM]={0};//记录六匹马跑的距离
    srand(time(0));//每次产生随机数 rand使用
    printf("\n-------比赛开始------\n");
    while(rank<=HORSENUM)//名次循环，直到6匹马的全部名次出来才结束
    {
	printf("\n-------比赛开始------\n");
	sleep(1);
        for(i=0;i<HORSENUM;i++)//6匹跑马循环
        {
                printf("%d号: ",i+1);//记录第一匹马到第六匹马

                dis[i]+=rand()%MAXSTEP+MINSTEP;//跑马的距离自加，馬每次跑的距离0-9
                //判断馬是否到终点，
                if(dis[i]>=LENGTH)
                {
                    dis[i]=LENGTH;
                    if(s[i]==0) //如果哪一匹馬到终点了，记录该匹马的名次
                        s[i]=rank++;
                }

                for(j=0;j<dis[i];j++)//打印跑马每次跑的距离
                    printf("-");

                if(s[i])//如果哪匹马到终点了，s[i]不为0，则打印出名次
                    printf("%d\n",s[i]);
                else
                    printf(">\n");

        }
    }



}

int main()
{
    int s[HORSENUM] ={0};//记录6匹马的最终名次，并全部初始化为0
    play(s);
    return 0;
}
