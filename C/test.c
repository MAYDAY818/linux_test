#include <math.h>
#include <stdio.h>

// double distance(double x1, double y1, double x2, double y2)
// {
// 	double dx = x2 - x1;
// 	double dy = y2 - y1;
// 	double dsquared = dx * dx + dy * dy;
// 	double result = sqrt(dsquared);
// 	return result;
// }

// int factorial(int n)
// {
// 	if (n == 0)
// 		return 1;
// 	else {
// 		int recurse = factorial(n-1);
// 		int result = n * recurse;
// 		return result;
// 	}
// }
// int euclid(int a,int b){
// 	if (a%b==0)
// 	{
// 		return b;
// 	}else{
// 		return euclid(b,a%b);
// 	}
// }

// int how_many_9(void)
// {
// 	int i = 1;
// 	int sum = 0;
// 	while(i<=100){
// 		if (i%10==9){
// 			sum++;
// 			printf("%d\n",i);
// 		}
// 		if(i/10==9){
// 			sum++;
// 			printf("%d\n",i);
// 		}
// 		i++;
// 	}
// 	return sum;
// }

	char stack[512];
	int top = -1;
	void push(char c)
	{
		stack[++top] = c;
	}
		char pop(void)
	{
		return stack[top--];
	}
		int is_empty(void)
	{
		return top == -1;
}

int main(void)
{
	// printf("distance is %f\n", distance(1.0, 2.0, 4.0, 6.0));
	// printf("%d\n",euclid(8,4));
	// printf("%d\n",euclid(12,7));
	// printf("%d\n",euclid(172,142));
	// printf("%d",how_many_9());
	int i, j;
	for (i=1; i<=9; i++) {
		for (j=1; j<=9&&j<=i; j++)
			printf("%d ", i*j);
		printf("\n");
		}
	return 0;
}
