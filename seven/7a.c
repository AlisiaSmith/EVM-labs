
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM 2048
#define M 1000

float maxRowSum(float *matrix, size_t size) {
	size_t i, j;
	float result, sum;
	result = 0.0f;
	for (i = 0; i < size; ++i) {
    	sum = 0.0f;
    	for (j = 0; j < size; ++j) {
        	sum += fabs(matrix[i * size + j]);
    	}
    	result = sum > result ? sum : result;
	}
	return result;
}

void transpose(float *result, float *matrix, size_t size) {
	size_t i, j;
	for (i = 0; i < size; ++i) {
    	for (j = 0; j < size; ++j) {
        	result[j * size + i] = matrix[i * size + j];
    	}
	}
}

void mulS(float *result, float *matrix, float scalar, size_t size) {
	size_t i, j;
	for (i = 0; i < size; ++i) {
    	for (j = 0; j < size; ++j) {
        	result[i * size + j] = matrix[i * size + j] * scalar;
    	}
	}
}

float *matrixTmpTransposed;
void mul(float *result, float *matrixA, float *matrixB, size_t size) {
	size_t i, j, k;
	transpose(matrixTmpTransposed,matrixB,size);
	for (i = 0; i < size; i++) {
    	for (j = 0; j < size; j++) {
        	float sum = 0;
        	for (k = 0; k < size; k++) {
            	sum += matrixA[i* size + k] * matrixTmpTransposed[j * size + k];
        	}
        	result[i * size + j] = sum;
    	}
	}

}

void add(float* result, float *matrixA, float *matrixB, size_t size) {
	size_t i, j;
	for (i = 0; i < size; ++i) {
    	for (j = 0; j < size; ++j) {
        	result[i * size + j] = matrixA[i * size + j] + matrixB[i * size + j];
    	}
	}
}

void sub(float* result, float *matrixA, float *matrixB, size_t size) {
	size_t i, j;
	for (i = 0; i < size; ++i) {
    	for (j = 0; j < size; ++j) {
        	result[i * size + j] = matrixA[i * size + j] - matrixB[i * size + j];
    	}
	}
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
    	}
    	printf("\n");
	}
}

int main() {
	size_t size = DIM;
	size_t m = M;
	size_t i, j;
	float *mem = malloc(7*size*size* sizeof(float));
	float *matrixA = mem;
	float *matrixB = mem + size * size;
	float *matrixR = mem + 2 * size * size;
	float *matrixI = mem + 3 * size * size;
	float *matrixT = mem + 4 * size * size;
	matrixTmpTransposed = mem + 5 * size * size;
	float *matrixAOld = mem + 6*size*size;
	float max_1;
	float max_inf;

	for (i = 0; i < size; ++i) {
    	for (j = 0; j < size; ++j) {
        	matrixA[i * size + j] = (i==j) ? (i+1) :0;//(float) rand() / (float) RAND_MAX * 10;
    	}
	}

	memcpy(matrixAOld, matrixA, size*size* sizeof(float));

	clock_t t = clock();

	max_1 = maxRowSum(matrixA, size);
	transpose(matrixB, matrixA, size);
	max_inf = maxRowSum(matrixB, size);

	mulS(matrixB, matrixB, 1/max_1/max_inf, size);
	mul(matrixR, matrixB, matrixA, size);
	identity(matrixI, size);
	sub(matrixR, matrixI, matrixR, size);
	memcpy(matrixA, matrixR, size * size * sizeof(float));

	for (i = 0; i < m; ++i) {
    	add(matrixI, matrixI, matrixA, size);
    	mul(matrixT, matrixA, matrixR, size);
    	matrixA = matrixT;
	}
	mul(matrixA, matrixI, matrixB, size);

	printf("A:\n");
	showMatrix(matrixAOld, size);
	printf("A^(-1):\n");
	showMatrix(matrixA, size);

	mul(matrixB, matrixA, matrixAOld, size);
	printf("A*A^(-1):\n");
	showMatrix(matrixB, size);
	printf("Time taken: %f seconds\n\r", (double)(clock() - t) / CLOCKS_PER_SEC);

	free(mem);

	return 0;
}
