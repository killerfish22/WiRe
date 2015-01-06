#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_matrix.h"

void dtrsv_(char *UPLO, char *TRANS, char *DIAG, INT * N, double *A, INT *LDA, double *RHS, INT *INCX); 
void dtrsm_(char *SIDE, char *UPLO, char *TRANS, char *DIAG, INT *M, INT *N, double *alpha, double *A, INT *LDA, double *RHS, INT *LDB); 

// Your functions here 


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
	printf("Reading the matrix took %lg seconds\n", toc - tic);

	// Create a Random n-by-100 matrix 
	my_matrix_rand(&RHS,A.rows, 100); 	

	// Your Code here....



	// Cleanup
	my_matrix_clear(&A); 
	my_matrix_clear(&RHS); 
	return 0; 

}
