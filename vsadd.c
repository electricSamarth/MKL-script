#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <time.h>

double* adder_vsadd(int runs, int dim){
	mkl_set_num_threads(mkl_get_max_threads());
	float *a, *b, *y;
	int n,i,r;
	n=dim;
	double s_initial, s_elapsed; // for time tracking
	
	a=(float*)mkl_malloc(n*sizeof(float),64);
	b=(float*)mkl_malloc(n*sizeof(float),64);
	y=(float*)mkl_malloc(n*sizeof(float),64);
	time_t t;
	srand((unsigned) time(&t));
	for(i=0;i<n;i++){
		a[i]=(float)(rand()%100);
		b[i]=(float)(rand()%100);
		y[i]=0;
	}
	



	vsAdd(n,a,b,y);

	s_initial=dsecnd();
	for(r=0; r<runs; r++){
		vsAdd(n, a, b, y);
	}
	double tom = (dsecnd()-s_initial);
	s_elapsed=tom/runs;
	//make a returner
	static double returner[2];
	returner[0]=s_elapsed*1000000;
	printf("%f",tom);
	returner[1]=(n)*1E-9/s_elapsed;

	//free what was allocated
	mkl_free(a);
	mkl_free(b);
	mkl_free(y);

	return returner;

	


//aa
}

int  main()
{
	double *time= adder_vsadd(1000000-1000,128*128);
	printf("the time is %f and gflops are %f \n",time[0],time[1]);
	return 0;
}