#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <time.h>

double* adder_axpy(int runs, int dim, int first)
{
	//define all the parameters
	float *x, *y;
	int n;
	float a;
	int incx, incy;
	int i;

	//initialize size
	n=dim;

	//other paras initialize
	a=1;
	incx=1;
	incy=1;

	//allocate memory to vectors
	x=(float*)mkl_malloc(n*sizeof(float),64);
	y=(float*)mkl_malloc(n*sizeof(float),64);

	//seed srand with time
	time_t t;
	srand((unsigned) time(&t));

	//populate the vectors with random vals and res with 0;
	for(i=0;i<n;i++){
		x[i]=(float)(rand()%10);
		y[i]=(float)(rand()%10);
	}

	//print x and y
	int j;
	printf("x: [");
	for(j=0; j<n; j++){
		printf("%f ",x[j]);
	}
	printf("] \n");

	printf("y: [");
	for(j=0; j<n; j++){
		printf("%f ",y[j]);
	}
	printf("] \n");


	//first call (to be ignored for benchmark)
	cblas_saxpy(n, a, x, incx, y, incy);

	//print y after ops
	printf("y_after_ops: [");
	for(j=0; j<n; j++){
		printf("%f ",y[j]);
	}
	printf("] \n");
}

int main(){
	int runs=1;
	int dim=3;
	int f=1;
	adder_axpy(runs,dim,f);
}