#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_matrix.h"

/* Here must be de declaration of the LAPACK functions you need.   */

// SUBROUTINE DGETRF( M, N, A, LDA, IPIV, INFO )
//SUBROUTINE DGETRS( TRANS, N, NRHS, A, LDA, IPIV, B, LDB, INFO )
void dgetrf_(int *M, int *N, double *A, int *lda, int *ipiv, int *info);
void dgetrs_(char *trans, int *N, int *nrhs, double *A, int *lda, int *ipiv, double *B, int *ldb, int *info);


int main (int argc , char *argv ){
	struct my_matrix_st A; 
	struct my_matrix_st RHS1, RHS2; 
	double tic,toc; 

	// read a dense matrix to A and measure the time
	tic = wtime(); 
	/*  Read the Matrix  */
	if ( my_matrix_read ("matrix.mtx", &A)){
		fprintf(stderr,"Can not read matrix.\n"); 
		return 1; 
	}
	/*  Read the first right hand side  */
	if ( my_matrix_read ("rhs1.mtx", &RHS1)){
		fprintf(stderr,"Can not read the first right hand side.\n"); 
		return 1; 
	}

	/*  Read the second right hand side  */
	if ( my_matrix_read ("rhs2.mtx", &RHS2)){
		fprintf(stderr,"Can not read the second right hand side.\n"); 
		return 1; 
	}

	toc = wtime(); 
	printf("Reading the matrix took %lg seconds\n", toc - tic);



	/*-----------------------------------------------------------------------------
	 *  Here begin your code. Solve A x = RHS1 and A y = RHS2 and write both 
	 *  soltion x and y to a file name "solution.dat" which has to look like: 
	 *
	 *   x_1 y_1 
 	 *   x_2 y_2 
	 *   ....
	 *   ...
	 *   x_n y_n 
	 *-----------------------------------------------------------------------------*/

	
	int M=A.rows;
	int N=A.cols;
	int nrhs=1;
	int *ipiv;
	ipiv=(int*)calloc(N,sizeof(int));
	int ldb=N;
	int info=0;
	
	dgetrf_(&M, &N, A.values, &M, ipiv, &info);
	dgetrs_("N", &M, &nrhs, A.values, &M, ipiv, RHS1.values, &N, &info);
	dgetrs_("N", &M, &nrhs, A.values, &M, ipiv, RHS2.values, &N, &info);
	
	FILE *fp;
	fp=fopen("solution.dat","w");
	int i;
	for(i=0;i<M;i++)
	{
	  fprintf(fp,"%f %f\n",RHS1.values[i],RHS2.values[i]);
	}
	
	free(ipiv);
		
	
	/* Do not change anything below */
	
	/* This line can be commeted out during development, but for the final result it is necessary.  */
	system("gnuplot ./display.plot"); 

	
	my_matrix_clear(&A); 
	my_matrix_clear(&RHS1); 
	my_matrix_clear(&RHS2); 
	return 0; 

}
