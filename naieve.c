#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <time.h>
double* nadd(double runs, int dim){
	
	float *a, *b, *y;
	int n,i;
	double r;
	n=dim;
	double s_initial, s_elapsed; // for time tracking
	
	a=(float*)malloc(n*sizeof(float));
	b=(float*)malloc(n*sizeof(float));
	y=(float*)malloc(n*sizeof(float));
	time_t t;
	srand((unsigned) time(&t));
	for(i=0;i<n;i++){
		a[i]=(float)(rand()%100);
		b[i]=(float)(rand()%100);
		
	}
	



	

	s_initial=dsecnd();
	for(r=0; r<runs; r++){
		for(i=0;i<n;++i){
			y[i]=a[i]+b[i];
		}
	}
	double tom = (dsecnd()-s_initial);
	s_elapsed=tom/runs;
	//make a returner
	static double returner[2];
	returner[0]=s_elapsed*1000000;
	printf("%f",tom);
	returner[1]=(n)*1E-9/s_elapsed;

	//free what was allocated
	free(a);
	free(b);
	free(y);

	return returner;
}

int main(){
	int map[]={4,8,16,32,64,128,256,512,128*7,1024,2048,4096};
    double runs[]={100000000*5,100000000,100000000,10000000*5,10000000,10000000,1000000*5,1000000, 1000000, 1000000, 1000000, 1000000};
    int iter;
    for(iter=0;iter<12;++iter){
        double *time=nadd(runs[iter],map[iter]);
        printf("for %d, the time is %f and gflops are %f \n",map[iter],time[0],time[1]);
    }
}
