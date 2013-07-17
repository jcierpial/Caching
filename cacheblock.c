#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "cacheblock.h"
//The entire code is explained in detail in Readme.pdf
int main()
{
	register int *a, ARRAY_SIZE = 1024, numIterations = 1024*1024, SOME_ACCESS_SIZE = 1048576; //All variables are initialized to powers of 2 for ease of calculation.
	int dummy, i, times;
	struct timeval start, end;
	float timeTaken2 = 1000, timeTaken1 = 1000; //Some arbitrary equal values so that the while loop can begin
	a = sbrk(4*1024*4096+8192);
	a = (int  *)((((int)a>>13)<<13)+8192);
	while(timeTaken2/timeTaken1 <= 1.6) //Experimenetation showed that the jump in time was approximately 1.5-1.6%
	{
		timeTaken1 = timeTaken2; //Sets the previous time counter to the time of the current run (saving the previous time value)
		SOME_ACCESS_SIZE /= 2; //Want to halve the access size (block size guess) each iteration
		gettimeofday(&start,NULL); //Start the timer
		for(times = 0; times < numIterations; times++) 
		{
			for(i = 0; i < ARRAY_SIZE; i+=SOME_ACCESS_SIZE)
				dummy = a[i];
		}
		gettimeofday(&end,NULL); //End the timer
		timeTaken2 = ((end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec))/(float)numIterations;
		printf("Guess: %d bytes: %f microseconds.\n",SOME_ACCESS_SIZE, timeTaken2);
	}
	return 0;
}