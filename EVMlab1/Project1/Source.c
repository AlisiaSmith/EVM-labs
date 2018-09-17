#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char **argv)
{
	unsigned int N = (unsigned int)atoi(argv[1]);
	long double Pi = 0;
	for (unsigned int i = 0; i <= N; i++)
		Pi = Pi + 4.0 * ((float) pow(-1, i) / (2.0 * (float)i + 1.0));
	printf("%Lf \n", Pi);
	return 0;
}
