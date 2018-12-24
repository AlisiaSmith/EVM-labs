#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>
 
#define DIM 8
#define M 1000
 
float maxRowSum(float *matrix, size_t size) {
	size_t i, j;
	float result = 0.0f;
	__m128 *mmMatrix = (__m128*) matrix;
	__m128 *block;
	const __m128 fabsMask = _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF));
	for (i = 0, block = mmMatrix; i < size; ++i) {
    	float sum = 0.0f;
    	__m128 mmSum = _mm_setzero_ps();
    	__m128 buf;
    	for (j = 0; j < size / 4; ++j, ++block) {
        	buf = _mm_load_ps((float*) block);
        	buf = _mm_and_ps(fabsMask, buf);
        	mmSum = _mm_add_ps(mmSum, buf);
    	}
    	buf = _mm_movehl_ps(buf, mmSum);
    	mmSum = _mm_add_ps(mmSum, buf); // 1 = 1+3, 2 = 2+4
    	buf = _mm_shuffle_ps(mmSum, mmSum, 1);
    	mmSum = _mm_add_ss(mmSum, buf); // 1 = 1+2
    	_mm_store_ss(&sum, mmSum); // 1 -> sum
    	result = (result > sum) ? result : sum;
	}
	return result;
}

float* matrixTmpTransposed;
void transpose(float *result, float *matrix, size_t size) {
	size_t i, j;
	__m128 *mmMatrix = (__m128*) matrix;
	__m128 *block;
	for (i = 0, block = mmMatrix; i < size; ++i) {
    	for (j = 0; j < size / 4; ++j, ++block) {
        	__m128 buf = _mm_load_ps((float*) block);
        	float tetrad[4];
        	_mm_store_ps(tetrad, buf);
        	result[(j * 4) * size + i] = tetrad[0];
        	result[(j * 4 + 1) * size + i] = tetrad[1];
        	result[(j * 4 + 2) * size + i] = tetrad[2];
        	result[(j * 4 + 3) * size + i] = tetrad[3];
    	}
	}
}
 
void mulS(float *result, float *matrix, float scalar, size_t size) {
	size_t i, j, k;
	__m128 *mmMatrix = (__m128*) matrix;
	__m128 *mmResult = (__m128*) result;
	__m128 mmScalar = _mm_load1_ps(&scalar);
	__m128 *block;
	for (i = 0, k = 0, block = mmMatrix; i < size; ++i) {
    	for (j = 0; j < size / 4; ++j, ++block, ++k) {
        	__m128 buf = _mm_load_ps((float*) block);
        	mmResult[k] = _mm_mul_ps(buf, mmScalar);
    	}
	}
}
 
void mul(float *result, float *matrixA, float *matrixB, size_t size) {
	size_t i, j, k;
	transpose(matrixTmpTransposed, matrixB, size);
	//c(i,j) = sum a(i,k)*bT(j,k)
   __m128 *m1 = (__m128*)matrixA;
	__m128 *m2 = (__m128*)matrixTmpTransposed;
 	for(i = 0; i < size; ++i) {
        	for(j = 0; j < size; ++j) {
            	__m128 mmSum = _mm_setzero_ps();
            	for(k = 0; k < size/4; k++) {
                	mmSum = _mm_add_ps(mmSum, _mm_mul_ps(m1[k], m2[k]));
            	}
            	float sum;
            	__m128 buf = _mm_movehl_ps(buf, mmSum);
            	mmSum = _mm_add_ps(mmSum, buf); // 1 = 1+3, 2 = 2+4
            	buf = _mm_shuffle_ps(mmSum, mmSum, 1);
            	mmSum = _mm_add_ss(mmSum, buf); // 1 = 1+2
            	_mm_store_ss(&sum, mmSum); // 1 -> sum
            	result[i*size+j] = sum;
            	m2+=size/4;;
        	}
        	m1+=size/4;
        	m2 = (__m128*)matrixTmpTransposed;
    	}
}
    
 
void identity(float *result, size_t size) {
	size_t i, j;
	memset(result, 0, size * size * sizeof(float));
	for (i = 0; i < size; ++i) {
    	result[i * (size + 1)] = 1;
	}
}
 
void add(float *result, float *matrixA, float *matrixB, size_t size) {
	size_t i, j;
	__m128 *mmMatrixA = (__m128*) matrixA;
	__m128 *mmMatrixB = (__m128*) matrixB;
	__m128 *mmResult = (__m128*) result;
	for (i = 0; i < size * size / 4; ++i) {
    	mmResult[i] = _mm_add_ps(mmMatrixA[i], mmMatrixB[i]);
	}
}
 
void sub(float *result, float *matrixA, float *matrixB, size_t size) {
 	size_t i, j;
	__m128 *mmMatrixA = (__m128*) matrixA;
	__m128 *mmMatrixB = (__m128*) matrixB;
	__m128 *mmResult = (__m128*) result;
	for (i = 0; i < size * size / 4; ++i) {
    	mmResult[i] = _mm_sub_ps(mmMatrixA[i], mmMatrixB[i]);
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

