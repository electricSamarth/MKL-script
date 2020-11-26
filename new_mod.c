#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <time.h>


float matmul(int runs, int dim,int first)
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
        return 1;
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

    
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                m, n, p, alpha, A, p, B, n, beta, C, n);

   
    s_initial = dsecnd();
    for (r = 0; r < runs; r++) {
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                    m, n, p, alpha, A, p, B, n, beta, C, n);
    }
    s_elapsed = (dsecnd() - s_initial) / runs;
    float returner=s_elapsed*1000;

    
    mkl_free(A);
    mkl_free(B);
    mkl_free(C);
    
    if (s_elapsed < 0.9/runs) {
        s_elapsed=1.0/runs/s_elapsed;
        i=(int)(s_elapsed*runs)+1;
        
    }
    
    if(first==0){
    //printf (" Example completed. \n\n");
    return returner;}
    else{
        matmul(i,dim,0);
    }
    
    
    
}

int main(){
    int map[]={4,8,16,32,64,128,256,512,128*7,1024,2048,4096};
    int iter;
    for(iter=0;iter<12;++iter){
        float time=matmul(1,map[iter],1);
        printf("for %d, the time is: %f\n",map[iter],time);
    }

}