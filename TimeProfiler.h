#pragma once

class TimeProfiler
{
public:
	char buf[1024];
	long startTime;
	TimeProfiler(const char * sign);
	~TimeProfiler();
};


#define PRIFILE_CODE_BLOCK_TIME(a) TimeProfiler timeProfilerBlock(a);