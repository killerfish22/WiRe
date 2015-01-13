#include<stdlib.h>
#include<stdio.h>


extern void dgeev_( char* jobvl, char* jobvr, int* n, double* a,
                int* lda, double* wr, double* wi, double* vl, int* ldvl,
                double* vr, int* ldvr, double* work, int* lwork, int* info );


void print_eigenvalues( char* desc, int n, double* wr, double* wi ) {
        int j;
        printf( "\n %s\n", desc );
   for( j = 0; j < n; j++ ) {
      if( wi[j] == (double)0.0 ) {
         printf( " %6.2f", wr[j] );
      } else {
         printf( " (%6.2f,%6.2f)", wr[j], wi[j] );
      }
   }
   printf( "\n" );
}

void print_eigenvectors( char* desc, int n, double* wi, double* v, int ldv ) {
        int i, j;
        printf( "\n %s\n", desc );
   for( i = 0; i < n; i++ ) {
      j = 0;
      while( j < n ) {
         if( wi[j] == (double)0.0 ) {
            printf( " %6.2f", v[i+j*ldv] );
            j++;
         } else {
            printf( " (%6.2f,%6.2f)", v[i+j*ldv], v[i+(j+1)*ldv] );
            printf( " (%6.2f,%6.2f)", v[i+j*ldv], -v[i+(j+1)*ldv] );
            j += 2;
         }
      }
      printf( "\n" );
   }
}

int main() 
{
	double A[16]={-3, 8, -2, 1, //
	   6, -4, 1,  5, //
	   2, 5, -8, 8, //
	   1, 5, -8, -7};
	
	int lwork=-1;
	int info=0;
	double wkopt;
	int n=4;
	int ldvl=4;
	int ldvr=4;
	
	double wr[4],wi[4],vl[4*4],vr[4*4];
	
	dgeev_( "V", "N", &n, A, &n, wr, wi, vl, &n, vr, &n, &wkopt, &lwork, &info );
	
	lwork = (int)wkopt;
        double* work = (double*)malloc( lwork*sizeof(double) );
	dgeev_( "V", "N", &n, A, &n, wr, wi, vl, &n, vr, &n, work, &lwork, &info );

        print_eigenvalues( "Eigenvalues", n, wr, wi );
        print_eigenvectors( "Eigenvectors", n, wi, vl, ldvl );

	return 0;
}

