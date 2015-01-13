#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_matrix.h"

//#define eight
#define nine

void dtrsv_(char *UPLO, char *TRANS, char *DIAG, INT * N, double *A, INT *LDA, double *RHS, INT *INCX); 
void dtrsm_(char *SIDE, char *UPLO, char *TRANS, char *DIAG, INT *M, INT *N, double *alpha, double *A, INT *LDA, double *RHS, INT *LDB); 

// Your functions here 
void L_solvev(struct my_matrix_st *L, double *b);
void L_solvev_trsv(struct my_matrix_st *L, double *b);
void L_solvem(struct my_matrix_st *L, struct my_matrix_st *B);
void L_solvem_trsv(struct my_matrix_st *L, struct my_matrix_st *B);
void L_solvem_trsm(struct my_matrix_st *L, struct my_matrix_st *B);

// 9th Homework
void scale_col(double s, struct my_matrix_st A, int i, int j, int col);
void r1_update(struct my_matrix_st A, int i, double s, double *v, int incv, double *w, int incw);

void demo_scale_col(struct my_matrix_st A);
void demo_r1_update(struct my_matrix_st A);


int main (int argc , char *argv ){
	struct my_matrix_st A; 
	struct my_matrix_st RHS; 
	double tic,toc; 

	// read a dense matrix to A and measure the time
	tic = wtime(); 
	if ( my_matrix_read ("demo100.mtx", &A)){
		fprintf(stderr,"Can not read matrix.\n"); 
		return 1; 
	}
	toc = wtime(); 
	//printf("Reading the matrix took %lg seconds\n", toc - tic);

	// Create a Random n-by-100 matrix 
	my_matrix_rand(&RHS,A.rows, 100); 	
	
	
	// Your Code here....
	struct my_matrix_st RHS2; 
	RHS2.cols=RHS.cols;
	RHS2.rows=RHS.rows;
	RHS2.LD=RHS.LD;
	RHS2.values=(double*)malloc(RHS2.rows*RHS2.cols*sizeof(double));
	dlacpy_("A",&(RHS.rows),&(RHS.cols),RHS.values,&(RHS.LD),RHS2.values,&(RHS2.LD));
	
	
	struct my_matrix_st RHS3; 
	RHS3.cols=RHS.cols;
	RHS3.rows=RHS.rows;
	RHS3.LD=RHS.LD;
	RHS3.values=(double*)malloc(RHS3.rows*RHS3.cols*sizeof(double));
	dlacpy_("A",&(RHS.rows),&(RHS.cols),RHS.values,&(RHS.LD),RHS3.values,&(RHS2.LD));
	
#ifdef eight
	
	tic = wtime();
	L_solvem(&A, &RHS);
	toc = wtime();
	printf("Compute the matrix by c) took %lg seconds\n", toc - tic);
	
	tic = wtime();
	L_solvem_trsv(&A, &RHS2);
	toc = wtime();
	printf("Compute the matrix by d) took %lg seconds\n", toc - tic);
	
	tic = wtime();
	L_solvem_trsm(&A, &RHS3);
	toc = wtime();
	printf("Compute the matrix by e) took %lg seconds\n", toc - tic);
	
#endif
	

#ifdef nine
	
	demo_scale_col(A);	
	demo_r1_update(A);
	
	
#endif
	
	// Cleanup
	my_matrix_clear(&A); 
	my_matrix_clear(&RHS); 
	my_matrix_clear(&RHS2); 
	my_matrix_clear(&RHS3); 
	return 0; 

}

#ifdef eight
void L_solvev(struct my_matrix_st *L, double *b)
{
  int i;
  for(i = 0; i < L->rows; i++)
  {
    int j;
    for(j = 0; j < i; j++)
    {
      b[i] -= (L->values[j * L->LD + i]) * b[j];
    }
    b[i] = 1/(L->values[j * L->LD + i]) * b[i];
  }
}

void L_solvev_trsv(struct my_matrix_st *L, double *b)
{
  int incx=1;
  dtrsv_("L", "N", "N", &(L->rows), L->values, &(L->LD), b, &incx); 
}

void L_solvem(struct my_matrix_st *L, struct my_matrix_st *B)
{
  int i;
  for(i = 0; i < B->cols; i++)
  {
    L_solvev(L, &(B->values[i * B->LD]));
  }
}

void L_solvem_trsv(struct my_matrix_st *L, struct my_matrix_st *B)
{
  int i;
  for(i = 0; i < B->cols; i++)
  {
    L_solvev_trsv(L, &(B->values[i * B->LD]));
  }
}

void L_solvem_trsm(struct my_matrix_st *L, struct my_matrix_st *B)
{
  int m = B->rows;
  int n = B->cols;
  double alpha = 1;
  dtrsm_("L", "L", "N", "N", &(m), &(n), &(alpha), L->values, &(L->LD), B->values, &(B->LD)); 
}
/*
OUTPUT:
 
demo100:
Reading the matrix took 0.0330969 seconds
Compute the matrix by c) took 0.000676008 seconds
Compute the matrix by d) took 0.00995489 seconds
Compute the matrix by e) took 0.000781101 seconds

demo2500:
Reading the matrix took 2.01327 seconds
Compute the matrix by c) took 3.52438 seconds
Compute the matrix by d) took 0.438389 seconds
Compute the matrix by e) took 0.463722 seconds

demo5625:
Reading the matrix took 22.2919 seconds
Compute the matrix by c) took 23.8809 seconds
Compute the matrix by d) took 1.78599 seconds
Compute the matrix by e) took 2.27577 seconds
*/

#endif

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
	
	/*
	OUTPUT:
	oldvalue newvalue
	1 		 2 
	-0.25 	 -0.5 
	0 		 0 
	0 		 0 
	0 		 0 
	0 		 0 
	0 		 0 
	0 		 0 
	0 		 0 
	0 		 0 
	-0.25 	 -0.5 
	...
	*/
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
	
	/*
	OUTPUT:
	oldvalue	newvalue
	-0.352867 	 5.64713 
	-0.0198928 	 7.98011 
	-0.00984245  9.99016 
	-0.00534529  11.9947 
	-0.00303501  13.997 
	-0.00167696  15.9983 
	-0.000752118 17.9992 
	*/
}