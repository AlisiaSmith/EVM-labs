#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

double foo(unsigned int x)
{
	if (x == 0) return 1;
	return pow(-1, x) / (2 * x + 1) + foo(x - 1);
}

int main(void)
{
	unsigned int N = 3500;
	double Pi = 0;
	time_t start, end;
	time(&start);
	Pi = foo(N);
	Pi = Pi * 4;
	time(&end);
	printf("%lf \n", Pi);
	printf("Time taken: %lf sec.\n", difftime(end, start));	return 0;

	//GetSystemTime();
}