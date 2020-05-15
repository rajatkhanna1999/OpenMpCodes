#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define ARR 512
int a[ARR][ARR];
int b[ARR][ARR];
int c[ARR][ARR];

int main(int argc, char* argv[]) 
{ 
    int nthreads, tid; 
    int i,j,k;
    double t1,t2;
    int sum=0;
    for(int i=0;i<ARR;i++)
    {
		for(int j=0;j<ARR;j++)
		{	
			a[i][j]=2;
			b[i][j]=2;
			c[i][j]=0;
		}
    }
    t1 =  omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(a,b,c)
    for( i=0;i<ARR;i++)
    {
		for( j=0;j<ARR;j++)
		{
			for( k=0;k<ARR;k++)
			{
				c[i][j]+=(a[i][k]*b[k][j]);
			}	
		}
    }
    t2 = omp_get_wtime();
	for( i=0;i<ARR;i++)
    {
		for( j=0;j<ARR;j++)
		{
			printf("%d ",c[i][j]);	
		}
		printf("\n");
   }
    printf("%f\n",t2-t1);
   return 0;
} 

