#pragma once

template <typename T>
void SafeRelease(T& obj)
{
	if (obj)
	{
		obj->Release();
		obj = nullptr;
	}
}

template <typename T>
void SafeDelete(T& obj)
{
	if (obj)
	{
		delete obj;
		obj = nullptr;
	}
}

struct DeleteMap
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = NULL;
		}
	}
};

struct DeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = NULL;
		}
	}
};

