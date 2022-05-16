#include <stdio.h>
#include <stdlib.h>
void newline(void)
{
	printf("\n");
}
int main(void)
{
	char *aeskey=(char *)malloc(16*sizeof(char));
	unsigned char aes_key[16] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
	printf("%ld\n",sizeof(aes_key));
	printf("%ld\n",sizeof(aeskey));
	printf("%s",aes_key);
	free(aeskey);
	return 0;
}
