//Nicholas Altice
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "threads.h"


int b = 0;
int e = 0;
Semaphore* *semArray;

void eat(int philosopherID);

int main()
{
	
    char c[17];
    fgets(c, 17, stdin); //get input
    int i = 0;
	while(c[i] >= 48 && c[i] <= 57 && i < 17){
    	b = (b * 10) + (c[i] - '0'); //get number of philosophers
    	i++;
	}
	i++;
	while(c[i] >= 48 && c[i] <= 57 && i < 17){
    	e = (e * 10) + (c[i] - '0'); //get number of entries
    	i++;
	}
	semArray = (struct Semaphore*)malloc(b * sizeof(struct Semaphore));
	for(int z = 0;z < b; z++){
		semArray[z] = (struct Semaphore*)malloc(sizeof(struct Semaphore));
    	InitSem(&semArray[z], 1);
	}
	
	int q[e];
    for(int z = 0;z < e; z++){
    	scanf("%d", &q[z]);
	}
	for(int z = 0;z < e; z++){
		start_thread(eat, q[z]);	
	}
    run();
    return 0;
}

void eat(int philosopherID)
{
	P(&semArray[(philosopherID - 1) % b]);
	yield();
	P(&semArray[(philosopherID) % b]);
	yield();
	printf("\n Philosopher %d is eating \n", philosopherID);
	V(&semArray[(philosopherID - 1) % b]);
	V(&semArray[(philosopherID) % b]);
	for(int z = 0;z < 300; z++){
    	yield();
	}
	return;
}


