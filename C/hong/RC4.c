#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <iostream>
 
using namespace std;
 
/*初始化S盒*/
void InitSbox(unsigned char sbox[]){
	for(int i = 0; i < 256; i++)  sbox[i] = i;
}
 
/*密钥填充256数组*/
void KeyExpansion(unsigned char key[], char *k, int len){
	if(len <= 256){
		for(int i = 0; i < 256; i++) key[i] = k[i % len];
	}
	if(len > 256){
		for(int i = 0; i < 256; i++) key[i] = k[i];
	}
}
 
/*打乱S盒*/ 
void UpsetSbox(unsigned char sbox[], unsigned char key[]){
	int j = 0;
	unsigned char temp;
	int n;
	for(int i = 0; i < 256; i++){
		n = j + (int)sbox[i] + (int)key[i];
		j = n % 256;
		temp = sbox[i];
		sbox[i] = sbox[j];
		sbox[j] = temp;
	}
}
 
/*加解密数据*/ 
void DataProcess(unsigned char sbox[], FILE *fp1, FILE *fp2){
	int i, j;
	i = 0; j = 0;
	char ch = fgetc(fp1);
	while(ch != EOF){
		i = (i + 1) % 256;
		int temp2 = j + (int)sbox[i];
		j = temp2 % 256;
		unsigned char temp;
		temp = sbox[i];
		sbox[i] = sbox[j];
		sbox[j] = temp;
		int temp1 = (int)sbox[i] + (int)sbox[j];
		int t = temp1 % 256;
		char k = sbox[t];
		char cipherchar = ch ^ k;
		fputc(cipherchar, fp2);
		ch = fgetc(fp1);
	}
}
 
/*加密总函数*/
void DataEncrypt(char *k, unsigned char *key, unsigned char *sbox, FILE *fp1, FILE *fp2) {
	int len = strlen(k);
    KeyExpansion(key, k, len);
    InitSbox(sbox);
    UpsetSbox(sbox, key);
    DataProcess(sbox, fp1, fp2);
    fclose(fp1);
    fclose(fp2);
    printf("\n加密成功!\n\n");
}
 
/*解密总函数*/ 
void DataDecrypt(char *k1, unsigned char *key, unsigned char *sbox, FILE *fp1, FILE *fp2) {
	int len = strlen(k1);
    KeyExpansion(key, k1, len);
    InitSbox(sbox);
    UpsetSbox(sbox, key);
    DataProcess(sbox, fp1, fp2);
    fclose(fp1);
    fclose(fp2);
    printf("\n解密成功!\n\n");
}
 
int main(){
	char *k = (char *)malloc(25 * sizeof(char));
	char *k1 = (char *)malloc(25 * sizeof(char));
	unsigned char key[256] = {0x00};
	unsigned char sbox[256] = {0x00};
	FILE *fp1, *fp2;
    int flag = 1;
    int choice;
    do{
    	printf("*****************************RC4加密解密文件************************************");
        printf("\n"); 
        printf("                             1.加密文件\n\n");
        printf("                             2.解密文件\n\n");
	    printf("                             3.退出\n\n"); 
	    printf("请选择要进行的操作:");
	    scanf("%d",&choice);
	    switch(choice){
		    case 1: fp1 = fopen("dec.txt","r");
		            if(fp1 == NULL){
    	                printf("打开源文件失败!\n");
    	                getchar();
    	                exit(0);
                    }
                    fp2 = fopen("RC4_ENC.txt","w");
                    if(fp2 == NULL){
    	                printf("打开加密后文件失败!\n");
    	                getchar();
    	                exit(0);
                    }
			        printf("\n请输入加密密钥:");
	                cin >> k;
	                DataEncrypt(k, key, sbox, fp1, fp2);
                    break;
			case 2: fp1 = fopen("RC4_ENC.txt","r");
			        if(fp1 == NULL){
    	                printf("打开加密后文件失败!\n");
    	                getchar();
    	                exit(0);
                    }
			        fp2 = fopen("RC4_DEC.txt","w");
			        if(fp2 == NULL){
    	                printf("打开解密后文件失败!\n");
    	                getchar();
    	                exit(0);
                    }
                    printf("\n请输入解密密钥:");
                    cin >> k1;
                    DataDecrypt(k1, key, sbox, fp1, fp2);
                    break;
            case 3: flag = 0;break;
            default : printf("\n操作不合法!\n\n");
	    }
    }while(flag);
}
