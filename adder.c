#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <time.h>

double* adder_axpy(int runs, int dim)
{
	//define all the parameters
	float *x, *y;
	int n;
	float a;
	int incx, incy;
	int i,r; //for looping
	double s_initial, s_elapsed; // for time tracking

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
		x[i]=(float)(rand()%100);
		y[i]=(float)(rand()%100);
	}

	// uncomment below to print x and y
	/*
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
	*/

	//first call (to be ignored for benchmark)
	cblas_saxpy(n, a, x, incx, y, incy);

	// uncomment to print y after ops
	/*
	printf("z: [");
	for(j=0; j<n; j++){
		printf("%f ",y[j]);
	}
	printf("] \n");
	*/
	//runs
	s_initial=dsecnd();
	for(r=0; r<runs; r++){
		cblas_saxpy(n, a, x, incx, y, incy);
	}
	double tom = (dsecnd()-s_initial);
	s_elapsed=tom/runs;
	//make a returner
	static double returner[2];
	returner[0]=s_elapsed*1000000;
	printf("%f",tom);
	returner[1]=(n)*1E-9/s_elapsed;

	//free what was allocated
	mkl_free(x);
	mkl_free(y);

	return returner;
}

int main(){
	int runs=1000000;
	int dim=128*128;
	int f=1;
	double *time=adder_axpy(runs,dim);
	printf("the time is %f and gflops are %f \n",time[0],time[1]);

}