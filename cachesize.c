#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "cachesize.h"
//The entire code is explained in detail in Readme.pdf
int main() 
{
	register *a;
    float timeTaken1 = 1, timeTaken2 = 1;
	int times, i, dummy, numIterations, memSize, cacheBlockSize = 64, ARRAY_SIZE = 200, SOME_ACCESS_SIZE = 10;
    struct timeval start, end;
	memSize = 4*1024*4096+8192;
    a = sbrk(memSize);
	a = (int *)((((int)a>>13)<<13)+8192);
	while(timeTaken2/timeTaken1 <= 2.3) //Experimenetation showed that the jump in time was approximately 2-2.3%
	{
		timeTaken1 = timeTaken2; //Sets the previous time counter to the time of the current run (saving the previous time value)
		ARRAY_SIZE *= 2; //Double the array size on each iteration
		numIterations = memSize/(ARRAY_SIZE * cacheBlockSize);  //Calculate smaller number of iterations for larger sized arrays
		gettimeofday(&start,NULL); //Start the timer
		for(times = 0; times < numIterations; times++) 
		{
			for(i = 0; i < ARRAY_SIZE; i+= SOME_ACCESS_SIZE)
				dummy = a[i];
		}
		gettimeofday(&end,NULL); //End the timer
		timeTaken2 = ((end.tv_sec*1000000+end.tv_usec)-(start.tv_sec*1000000+start.tv_usec))/(float)numIterations;
		printf("The access time for access size %d kilobytes is %f microseconds\n", (ARRAY_SIZE * cacheBlockSize)/1024, timeTaken2);
	}
	return 0;
}