#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	unsigned int N = (unsigned int)atoi(argv[1]);
	long double Pi = 0;
	int k;
	for (unsigned int i = 0; i <= N; i++)
	{
		if (i % 2 == 0) k = 1;
		else k = -1;
		Pi = Pi + ( k / (2.0 * (float)i + 1.0));
	}
		Pi *= 4.0;
	printf("%Lf \n", Pi);
	return 0;
}
