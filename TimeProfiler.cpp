#include "stdafx.h"

#include <iostream>
#include <stdarg.h>
#include <vector>


#if defined(_WIN32)
#include <windows.h>
#elif defined(OS_ANDROID)
#include <android/log.h>
#endif
unsigned long getSysTime()
{
#if defined(WIN32)
	return (unsigned long)GetTickCount();
#else 
	timeval tv;
	gettimeofday(&tv, 0);
	return (unsigned long long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#endif
}
struct recordItem
{
	std::string name;
	long time;
	int stackDeep;
};
std::vector<recordItem*> resultList;
std::vector<std::string> stackList;

TimeProfiler::TimeProfiler(const char * sign)
{
	strcpy(buf, sign);
	startTime = getSysTime();
	stackList.push_back(sign);
}
TimeProfiler::~TimeProfiler()
{
	recordItem*aItem = new recordItem();
	aItem->name = buf;
	aItem->time = getSysTime() - startTime;
	aItem->stackDeep = stackList.size() - 1;
	resultList.push_back(aItem);
	stackList.pop_back();
}

void printProfileAllStack()
{
	char buf[1024];
	for (int i = 0; i < resultList.size(); i++){
		recordItem * t = resultList[i];
		sprintf(buf, "%s:%d_%d", t->name.c_str(), t->stackDeep, t->time);
		printf("%s",buf);
		delete t;
	}
	resultList.clear();
}