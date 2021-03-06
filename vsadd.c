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
	int map[]={4,8,16,32,64,128,256,512,128*7,1024,2048,4096};
    int runs[]={100000000,100000000,100000000,100000000,100000000,100000000,100000000,100000000, 100000000, 100000000, 100000000, 100000000};
    int iter;
    for(iter=0;iter<12;++iter){
        double *time=adder_vsadd(runs[iter],map[iter]);
        printf("for %d, the time is %f and gflops are %f \n",map[iter],time[0],time[1]);
    }
}