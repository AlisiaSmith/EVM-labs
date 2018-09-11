#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>


int main(void)
{
	unsigned int N = //1000;
					1200000000; // 15 // 22,8
					//1500000000; // 18
	long double Pi = 0;
	long double start, end;
	
	start = GetTickCount(); // имеет погрешность в 10 мс
	for (int i = 0; i <= N; i++)
		Pi = Pi + pow(-1, i) / (2 * i + 1);
	Pi = Pi * 4;
	end = GetTickCount();

	printf("pi = %lf \n", Pi);
	printf("Time of work: %lf sec.\n", (end - start) / 1000);	
	return 0;

}