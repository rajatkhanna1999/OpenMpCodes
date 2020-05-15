#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define MAX_SIZE 1000
int a[MAX_SIZE];

/*Code is Submitted by:
 *Rajat Khanna(2017UCS0050)
 *EmailId: 2017ucs0050@iitjammu.ac.in*/

/*export OMP_NUM_THREADS=5
 *gcc -fopenmp quickSort.c*/

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}

int split(int arr[],int low, int high, int pivot)  
{  
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)  
    {  
        if (arr[j] < pivot)  
        {  
            i++; 
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  

void quickSort(int start, int end){
	if(start == end){
		return;
	}
	int pivot = a[start];
	int mid = split(a,start,end,pivot);
	#pragma omp task
	quickSort(start, mid-1);
	#pragma omp task
	quickSort(mid, end);
	#pragma omp taskwait
}

int main(int argc, char* argv[]) 
{ 
    // Uncomment This to take input in a file and output in a file
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    // #endif

    //Input Number of elements
    int n;
    scanf("%d",&n);

    //Input Array Elements
    for(int i = 0; i < n; i++){
        scanf("%d",&a[i]);
    }

    double t1,t2;
    t1 =  omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        quickSort(0,n-1);
        #pragma omp barrier
    }
    t2 = omp_get_wtime();
    printf("Time Taken: %f\n",t2-t1);

    
   for(int i = 0; i < n; i++){
	printf("%d\n",a[i]);
   }
   return 0;
} 
