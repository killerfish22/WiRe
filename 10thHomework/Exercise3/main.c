#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_matrix.h"

void dtrsv_(char *UPLO, char *TRANS, char *DIAG, INT * N, double *A, INT *LDA, double *RHS, INT *INCX); 
void dtrsm_(char *SIDE, char *UPLO, char *TRANS, char *DIAG, INT *M, INT *N, double *alpha, double *A, INT *LDA, double *RHS, INT *LDB); 

// Your functions here 
void scale_col(double s, struct my_matrix_st A, int i, int j, int col);
void r1_update(struct my_matrix_st A, int i, double s, double *v, int incv, double *w, int incw);
void LU(struct my_matrix_st A);
void LU_solve(struct my_matrix_st LU, double *b);

void demo_scale_col(struct my_matrix_st A);
void demo_r1_update(struct my_matrix_st A);


int main (int argc , char *argv ){
	struct my_matrix_st A; 
	A.LD = 6;
	A.cols = 6;
	A.rows = 6;
	A.values = (double*) malloc(sizeof(double) * 6 * 6);
	
	int j;
	int k;
	for(j = 0; j < 6; j++)
		for (k = 0; k < 6; k++)
			A.values[k + j * A.LD] = 1./(1+k+j);


	double b[] = {49./20, 223./140, 314./280, 2509./2520, 2131./2520, 20417./27720};
	
	LU(A);
	LU_solve(A, b);
	
	int i;
	for(i = 0; i < 6; i++)
	{
		printf("%lg \n", b[i]);
	}
	
	// Cleanup
	//my_matrix_clear(&A); 
	return 0; 

}

void scale_col(double s, struct my_matrix_st A, int i, int j, int col)
{
	const int pos = col * A.LD;
	for(i = i; i <= j; i++)
    {
		A.values[i + pos] *= s;
    }
}

void r1_update(struct my_matrix_st A, int i, double s, double *v, int incv, double *w, int incw)
{
	int j;
	int k;
	for(j=i; j < A.cols; j++)
	{
		for(k = i; k < A.rows; k++)
		{
			A.values[k + j * A.LD] += s * v[(k-i)*incv] * w[(j-i)*incw];
		}
	}
}

void LU(struct my_matrix_st A)
{
	int k;
	for(k = 1; k < A.cols; k++)
	{
		if (A.values[k + k * A.LD] == 0) printf("Divide by zero\n");
		scale_col(1./A.values[k + k * A.LD], A, k + 1, A.rows, k);
		r1_update(A, k + 1, -1, &(A.values[(k+1)+(k*A.LD)]), 1 , &(A.values[(k)+(k+1*A.LD)]), A.LD);
	}
}

void LU_solve(struct my_matrix_st LU, double *b)
{
	int incv = 1;
	//Solve Ly = b for y = Ux
	dtrsv_ ("L", "N", "N", &LU.cols, LU.values, &LU.LD, b, &incv);
	//Solve Ux = y
	dtrsv_ ("U", "N", "N", &LU.cols, LU.values, &LU.LD, b, &incv);
}

void demo_scale_col(struct my_matrix_st A)
{
	int i;
	double* b;
	b = (double*) malloc(sizeof(double) * A.rows);
	for (i = 0; i < A.rows; i++)
	{
		b[i] = A.values[i];
	}
	
	double s = 2.0;
	int firstRow = 0;
	int lastRow = 90;
	scale_col(s, A, firstRow, lastRow, 0);
	
	printf("oldvalue\tnewvalue\n");
	for (i = 0; i < A.rows; i++)
	{
	  printf("%lg \t\t %lg \n", b[i], A.values[i]);
	}
	printf("\n");
}

void demo_r1_update(struct my_matrix_st A)
{
	int i;
	double* b;
	b = (double*) malloc(sizeof(double) * A.rows);
	for (i = 0; i < A.rows; i++)
	{
		b[i] = A.values[i + 92 * A.LD];
	}
	
	int startRow = 90;
	double s = 1.0;
	double* v;
	v = (double*) malloc(sizeof(double) * 20);
	double* w;
	w = (double*) malloc(sizeof(double) * 20);
	
	for (i = 0; i < 20; i++)
	{
		v[i] = i;
		w[i] = 1;
	}
	
	r1_update(A, startRow, s, v, 2, w, 2);
	
	printf("oldvalue\tnewvalue\n");
	for (i = 93; i < A.rows; i++)
	{
	  printf("%lg \t %lg \n", b[i], A.values[i + 92 * A.LD]);
	}
	printf("\n");
}