#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_matrix.h"

void dtrsv_(char *UPLO, char *TRANS, char *DIAG, INT * N, double *A, INT *LDA, double *RHS, INT *INCX); 
void dtrsm_(char *SIDE, char *UPLO, char *TRANS, char *DIAG, INT *M, INT *N, double *alpha, double *A, INT *LDA, double *RHS, INT *LDB); 

// Your functions here 
void L_solvev(struct my_matrix_st *L, double *b);
void L_solvev_trsv(struct my_matrix_st *L, double *b);
void L_solvem(struct my_matrix_st *L, struct my_matrix_st *B);
void L_solvem_trsv(struct my_matrix_st *L, struct my_matrix_st *B);
void L_solvem_trsm(struct my_matrix_st *L, struct my_matrix_st *B);

int main (int argc , char *argv ){
	struct my_matrix_st A; 
	struct my_matrix_st RHS; 
	double tic,toc; 

	// read a dense matrix to A and measure the time
	tic = wtime(); 
	if ( my_matrix_read ("demo5625.mtx", &A)){
		fprintf(stderr,"Can not read matrix.\n"); 
		return 1; 
	}
	toc = wtime(); 
	printf("Reading the matrix took %lg seconds\n", toc - tic);

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
	
#if 0
	double* b;
	double* c;
	b = (double*) malloc(sizeof(double) * 100);
	c = (double*) malloc(sizeof(double) * 100);
	int i;
	for (i = 0; i < 100; i++)
	{
	  b[i] = 1;
	  c[i] = 1;
	}
	
	L_solvem(&A, &RHS);
	L_solvem_trsv(&A, &RHS2);
	L_solvem_trsm(&A, &RHS3);
	
	for (i = 0; i < 100; i++)
	{
	  printf("%lg ", RHS.values[i]);
	  printf("%lg ", RHS2.values[i]);
	  printf("%lg ", RHS3.values[i]);
	}
	printf("\n");
	
	/*
	for (i = 0; i < 100; i++)
	{
	  printf("%lg ", c[i]);
	}
	printf("\n");
	*/
#endif
	
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
	
	// Cleanup
	my_matrix_clear(&A); 
	my_matrix_clear(&RHS); 
	my_matrix_clear(&RHS2); 
	my_matrix_clear(&RHS3); 
	return 0; 

}

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