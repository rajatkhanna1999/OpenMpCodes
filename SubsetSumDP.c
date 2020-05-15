#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define MAX_SIZE 1000
int a[MAX_SIZE];
int dp[MAX_SIZE][MAX_SIZE];

/*Code is Submitted by:
 *Rajat Khanna(2017UCS0050)
 *EmailId: 2017ucs0050@iitjammu.ac.in*/

/*export OMP_NUM_THREADS=5
 *gcc -fopenmp SubsetSumDP.c*/

int IsSubsetSum(int idx, int sum){
    if(sum==0){
        return 1;
    }
    if(idx==0){
        return 0;
    }
    if(dp[idx][sum]!=-1){
        return dp[idx][sum];
    }
    #pragma omp task
    dp[idx][sum] = IsSubsetSum(idx-1,sum);

    #pragma omp taskwait

    if(a[idx-1]<=sum){
        #pragma omp task
        dp[idx][sum]|=IsSubsetSum(idx-1,sum-a[idx-1]);
    }

    #pragma omp taskwait
    return dp[idx][sum];
}


int main(int argc, char* argv[]) 
{ 
    // Uncomment This to take input in a file and output in a file
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    // #endif

    //Asumming n<=1000 and sum<=1000 as max size defined is 1000

    //Input Number of elements
    int n;
    scanf("%d",&n);

    //Input Sum of elements
    int sum;
    scanf("%d",&sum);

    //Input Array Elements
    for(int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }

    //Initialising dp array with -1 
    //memset(dp,-1,sizeof(dp)); // memset can be also used
    for(int i=0; i<MAX_SIZE; i++){
        for(int j=0; j<MAX_SIZE; j++){
            dp[i][j] = -1;
        }
    }
    int ans;

    double t1,t2;
    t1 =  omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        ans = IsSubsetSum(n,sum);
        #pragma omp barrier
    }
    t2 = omp_get_wtime();
    printf("Time Taken: %f\n",t2-t1);

    if(ans==1){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
   return 0;
} 

/*
Sample Input:
6
9
3 34 4 12 5 2
Output:
Time Taken: 0.001851
YES
*/
