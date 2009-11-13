#include <time.h>

clock_t startTime = 0;
clock_t middleEnd = 0;
clock_t middleBegin = 0;
clock_t endTime = 0;
clock_t curtime = 0;
double timePerIteration = 0;

clock_t getBeginTime()
{
	clock_t beginTime;
	clock_t lastTime = clock();
	while((beginTime = clock()) == lastTime);
	return beginTime;
}
	
clock_t getEndTime()
{
	unsigned int i = 0;
	clock_t beginTime = clock();
	clock_t endTime = beginTime;
	clock_t newEnd;
	while((endTime = clock()) == beginTime) ++i;
	
	newEnd = endTime - (clock_t)(timePerIteration * (double)(i));
	return (newEnd > beginTime) ? newEnd : beginTime;
}


void start_timer()
{
	middleEnd = 0;
	middleBegin = 0;
	endTime = 0;
	curtime = 0;
	
	startTime = getBeginTime();
}

void middle_time()
{
	middleEnd = getEndTime();
	middleBegin = getBeginTime();
}

double time_elapsed()
{
	return (double)(clock() - startTime) / (double)(CLOCKS_PER_SEC);
}

void stop_timer()
{
	endTime = getEndTime();
	
	if(middleEnd){
		curtime = (endTime - middleEnd) - (middleBegin - startTime);
	}else{
		curtime = endTime - startTime;
	}
}

double getSecs()
{
	return (double)(curtime) / (double)(CLOCKS_PER_SEC);
}

double getNanoPerN(unsigned int N)
{
	return (getSecs() / (double)(N)) * (double)(1.0e9);
}

void calibrate_timer()
{
	/* Calculating timePerIteration this will take arround a second. */
	clock_t real_begin;
	clock_t real_end;
	unsigned int i = 0;
	clock_t lastTime = getBeginTime();
	real_begin = lastTime;
	real_end = real_begin + CLOCKS_PER_SEC;
	/* Looks a lot like the loop in getEndTime */
	while((lastTime = clock()) < real_end)	++i;
	
	timePerIteration = (double)(i) / (double)(lastTime - real_begin);
}

void printStatus()
{
	printf("startTime = %lu, middleEnd = %lu, middleBegin = %lu, endTime = %lu, curtime = %lu, timePerIteration = %f\n", 
		startTime, middleEnd, middleBegin, endTime, curtime, timePerIteration);
}
