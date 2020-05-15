#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define ARR 1000000
int a[ARR];

int main(int argc, char* argv[]) 
{ 
    int nthreads, tid; 
    double t1,t2;
    int sum=0;
    for(int i=0;i<ARR;i++)
    {
	a[i]=1;
    }
    t1 =  omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<ARR;i++)
    {
	      sum+=a[i];
    }

    t2 = omp_get_wtime();
    printf("%d\n",sum);
    printf("%f\n",t2-t1);
   return 0;
} 

