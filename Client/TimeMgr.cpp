#include "stdafx.h"
#include "TimeMgr.h"


IMPLEMENT_SINGLETON(TimeMgr);

TimeMgr::TimeMgr()
{
}


TimeMgr::~TimeMgr()
{
}

void TimeMgr::InitTime()
{
	QueryPerformanceCounter(&mFrameTime);
	QueryPerformanceCounter(&mFixTime);
	QueryPerformanceCounter(&mLastTime);

	QueryPerformanceFrequency(&mCpuTick);
}

void TimeMgr::SetTime()
{
	QueryPerformanceCounter(&mFrameTime);

	if (mFrameTime.QuadPart - mLastTime.QuadPart > mCpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&mCpuTick);
		mLastTime.QuadPart = mFrameTime.QuadPart;
	}

	mTime = float(mFrameTime.QuadPart - mFixTime.QuadPart) / mCpuTick.QuadPart;
	mFixTime = mFrameTime;
}


