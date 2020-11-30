#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <time.h>


double* matmul(int runs, int dim)
{
    float *A, *B, *C;
    int m, n, p, i, r;
    double alpha, beta;
    double s_initial, s_elapsed;

    
    m = dim, p = dim, n = dim;
  
    alpha = 1.0; beta = 0.0;

  
    A = (float *)mkl_malloc( m*p*sizeof( float ), 64 );
    B = (float *)mkl_malloc( p*n*sizeof( float ), 64 );
    C = (float *)mkl_malloc( m*n*sizeof( float ), 64 );
    if (A == NULL || B == NULL || C == NULL) {
        mkl_free(A);
        mkl_free(B);
        mkl_free(C);(s_elapsed * 1000);
    }
    time_t t;
    srand((unsigned)time(&t));
    for (i = 0; i < (m*p); i++) {
        A[i] = (float)(rand() % 10);
    }

    for (i = 0; i < (p*n); i++) {
        B[i] = (float)(rand() % 10);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }
    int max_threads = mkl_get_max_threads();

    printf ("%d threads, total_time_sec: ", max_threads);
     mkl_set_num_threads(max_threads);

    
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, p, alpha, A, p, B, n, beta, C, n);

   
    s_initial = dsecnd();
    for (r = 0; r < runs; r++) {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                    m, n, p, alpha, A, p, B, n, beta, C, n);
    }
    double lom=(dsecnd() - s_initial);
    printf("%f ",lom);
    s_elapsed=lom/runs;
    static double returner[2];
    returner[0]=s_elapsed*1000;
    returner[1]=(2.0*m*n*p)*1E-9/s_elapsed;

    
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);
    
    

    return returner;
    
    
    
    
}

int main(){
    int map[]={4,8,16,32,64,128,256,512,128*7,1024,2048,4096};
    int runs[]={10000000,10000000,10000000,10000000,1000000,100000,10000,10000, 1000, 1000, 100, 10};
    int iter;
    for(iter=0;iter<12;++iter){
        double *time=matmul(runs[iter],map[iter]);
        printf("for %d, the time is %f and gflops are %f \n",map[iter],time[0],time[1]);
    }

}