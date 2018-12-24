
#include <cblas.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 2048
#define M 10

float maxRowSum(float *matrix, size_t size) {
	size_t i;
	float sums[size];
	for (i = 0; i < size; ++i) {
    	sums[i] = cblas_sasum(size, matrix + size * i, 1); //sasum сумма элементов в векторе по модулю
	}
	return sums[cblas_isamax(size, sums, 1)];  //cblas_isamax - индекс вектора с наибольшим значением
}

float maxColumnSum(float *matrix, size_t size) {
	size_t i;
	float sums[size];
	for (i = 0; i < size; ++i) {
    	sums[i] = cblas_sasum(size, matrix + i, size);
	}
	return sums[cblas_isamax(size, sums, 1)];
}

void identity(float* result, size_t size) {
	size_t i, j;
	memset(result, 0, size * size * sizeof(float));
	for (i = 0; i < size; ++i) {
    	result[i * (size + 1)] = 1;
	}
}

void showMatrix(float *matrix, size_t size) {
	size_t i, j;
	for (i = 0; i < size; ++i) {
    	for (j = 0; j < size; ++j) {
        	printf("%f ", matrix[i * size + j]);
        	printf(" ");
    	}
    	printf("\n");
	}
}

int main() {
	size_t size = DIM;
	size_t m = M;
	size_t i, j;
	float *mem = malloc(5 * size * size * sizeof(float));
	float *matrixA = mem;
	float *matrixR = mem + 1 * size * size;
	float *matrixI = mem + 2 * size * size;
	float *matrixM = mem + 3 * size * size;
	float *matrixT = mem + 4 * size * size;
	float max_1;
	float max_inf;

	for (i = 0; i < size; ++i) {
    	for (j = 0; j < size; ++j) {
        	matrixA[i * size + j] = (float) rand() / (float) RAND_MAX * 10;
    	}
	}

	clock_t t = clock();

	max_1 = maxRowSum(matrixA, size);
	max_inf = maxColumnSum(matrixA, size);

	cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, size, size, size, 1.0/max_1/max_inf, matrixA, size, matrixA, size, 0, matrixR, size);  // R=B*A

	identity(matrixI, size);
	cblas_saxpy(size * size, -1.0f, matrixI, 1, matrixR, 1); //(-1)*I+R
	memcpy(matrixM, matrixR, size * size * sizeof(float));   // M=R

	for (i = 0; i < m; ++i) {
    	cblas_saxpy(size * size, 1.0f, matrixM, 1, matrixI, 1);
    	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size, size, size, 1.0f, matrixM, size, matrixR, size, 0, matrixT, size);
    	matrixM = matrixT;
	}
	cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, size, size, size, 1.0f, matrixA, size, matrixI, size, 0, matrixT, size);

	printf("Time taken: %f seconds\n\r", (double)(clock() - t) / CLOCKS_PER_SEC);
	showMatrix(mem,size);

	free(mem);

	return 0;
}
