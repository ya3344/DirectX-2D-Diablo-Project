#pragma once
class TimeMgr
{
	DECLARE_SINGLETON(TimeMgr);
private:
	TimeMgr();
	~TimeMgr();

public:
	const float& GetTime() const { return mTime; };

public:
	void InitTime();
	void SetTime();
	

private:
	LARGE_INTEGER mFrameTime = {};
	LARGE_INTEGER mFixTime = {};
	LARGE_INTEGER mLastTime = {};
	LARGE_INTEGER mCpuTick = {};

private:
	float mTime = 0.f;
};

