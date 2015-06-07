#ifndef __FPSCOUNTER_H__
#define __FPSCOUNTER_H__

#include "Singleton.h"

namespace Framework
{
	class FPSCounter
		: public Singleton<FPSCounter>
	{
	public:
		FPSCounter() : mPCFreq(0.0f), CounterStart(0), lastCounter(0.0f), maxCounter(0.00000001f), minCouter(999999999.0f){};
		~FPSCounter() {};

		void StartCounter();
		void StartCounterTest1();
		double GetCounterTest1();

		double GetCounter();
		double GetLastCounter() { return lastCounter; };
		double GetMinCounter() { return minCouter; }
		double GetMaxCounter() { return maxCounter; }
		double GetLastCounterTest1() { return lastCounterTest1; };
	private:
		double mPCFreq;
		double lastCounter;
		__int64 CounterStart;
		
		__int64 CounterStartTest1;
		double lastCounterTest1;

		double minCouter;
		double maxCounter;
	};

	inline void FPSCounter::StartCounterTest1()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			exit(0);


		//mPCFreq = double(li.QuadPart) / 1000.0;//miliseconds
		mPCFreq = double(li.QuadPart);//miliseconds

		QueryPerformanceCounter(&li);
		CounterStartTest1 = li.QuadPart;

	}
	inline void FPSCounter::StartCounter()
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			exit(0);


		//mPCFreq = double(li.QuadPart) / 1000.0;//miliseconds
		mPCFreq = double(li.QuadPart);//miliseconds

		QueryPerformanceCounter(&li);
		CounterStart = li.QuadPart;
		
	}
	inline double FPSCounter::GetCounter()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		double counter = double(li.QuadPart - CounterStart) / mPCFreq;//mili
		if (counter < minCouter)
			minCouter = counter;
		if (counter > maxCounter)
			maxCounter = counter;
		lastCounter = counter;

		return counter;
	}
	inline double FPSCounter::GetCounterTest1()
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		double counter = double(li.QuadPart - CounterStartTest1) / mPCFreq;//mili
		
		lastCounterTest1 = counter;
		
		return counter;
	}

}

#endif