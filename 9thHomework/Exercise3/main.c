#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my_matrix.h"

// Your functions here 
void scale_col(double s, struct my_matrix_st A, int i, int j, int col);
void r1_update(struct my_matrix_st A, int i, double s, double *v, int incv, double *w, int incw);

void demo_scale_col(struct my_matrix_st A);
void demo_r1_update(struct my_matrix_st A);


int main (int argc , char *argv ){
	struct my_matrix_st A; 

	// read a dense matrix to A
	if ( my_matrix_read ("demo100.mtx", &A)){
		fprintf(stderr,"Can not read matrix.\n"); 
		return 1; 
	}	

	demo_scale_col(A);	
	demo_r1_update(A);
	
	// Cleanup
	my_matrix_clear(&A); 
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