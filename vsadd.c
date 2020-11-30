#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <time.h>

double* adder_vsadd(int runs, int dim){
	float *a, *b, *y;
	int n;
	n=dim;
	x=(float*)mkl_malloc(n*sizeof(float),64);
	y=(float*)mkl_malloc(n*sizeof(float),64);
	time_t t;
	srand((unsigned) time(&t));
	for(i=0;i<n;i++){
		a[i]=(float)(rand()%100);
		b[i]=(float)(rand()%100);
		y[i]=0;
	}
	int j;
	printf("x: [");
	for(j=0; j<n; j++){
		printf("%f ",a[j]);
	}
	printf("] \n");

	printf("y: [");
	for(j=0; j<n; j++){
		printf("%f ",b[j]);
	}
	printf("] \n");



	vsAdd(n,a,b,y);


	printf("z: [");
	for(j=0; j<n; j++){
		printf("%f ",y[j]);
	}
	printf("] \n");
	



}

int  main()
{
	adder_vsadd(1,3)
	return 0;
}