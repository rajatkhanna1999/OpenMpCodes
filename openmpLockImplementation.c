#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define MAX_SIZE 1000

/*Code is Submitted by:
 *Rajat Khanna(2017UCS0050)
 *EmailId: 2017ucs0050@iitjammu.ac.in*/

/*To compile use
 *export OMP_NUM_THREADS=5
 *gcc -fopenmp openmpLock.c*/

/*Ticket Lock Data Structure:
 * Contains:
 * 1. next_ticket: value of the next ticket that can be obtained while acquirng a lock
 * gets incremented on each lock request
 * 2. now_serving: ticket value that is being serviced with the lock at present*/

typedef struct Ticket_Lock{
	int nextTicket;
	int nowServing;
}My_Lock;

int FetchAndAdd(int *ptr) {
	int old ;
	#pragma omp atomic capture
    {
        (*ptr)++;
        old = *ptr;
    }
	return old;
}

void mylock_init(My_Lock* lock){
	lock->nextTicket = 0;
	lock->nowServing = 1;
}

void mylock_lock(My_Lock* lock){
	int myTicket = FetchAndAdd(&lock->nextTicket);
    while(1){
    	if(myTicket == lock->nowServing){
    		return ;
    	}
    }
}

void mylock_unlock(My_Lock* lock){
	#pragma omp atomic 
    lock->nowServing++;
}

void mylock_destroy(My_Lock* lock){
	free(lock);
}

int main(int argc, char* argv[]) 
{ 
    int a[MAX_SIZE];
    for(int i=0; i<MAX_SIZE; i++){
    	a[i] = 1;
    }
    int ans = 0, i = 0;

    //Allocating Memory 
    My_Lock *lock = malloc(sizeof(My_Lock));
    mylock_init(lock); //Initializing a lock
    #pragma omp parallel for default (shared) private (i)
    for(i=0;i<MAX_SIZE;i++)
    {
        mylock_lock(lock);  //Acquiring a lock                    
        ans += a[i];                        
        mylock_unlock(lock);  //Releasing the lock
    }
    printf("Sum of array is : %d\n", ans);
    mylock_destroy(lock); //Destroying the lock

    return 0;
} 
