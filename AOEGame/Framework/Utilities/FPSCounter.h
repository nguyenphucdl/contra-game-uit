#ifndef __FPSCOUNTER_H__
#define __FPSCOUNTER_H__

#include "Singleton.h"

namespace Framework
{
	class FPSCounter
		: public Singleton<FPSCounter>
	{
	public:
		FPSCounter();
		~FPSCounter() {};

		void StartCounter();
		double GetCounter();		
		void	StartTimeCounter(int counterIdx);
		double	GetTimerCounter(int counterIdx);
		double  GetMaxTimeCounter(int counterIdx);
		double  GetMinTimeCounter(int counterIdx);
		void	StartLoopCounter(int counterIdx);
		void	IncreaseLoopCounter(int counterIdx);
		void	ResetTimeCounter(int counterIdx);
		int	GetLoopCounter(int counterIdx);

	private:
		double mPCFreq;
		__int64 CounterStart;
		
		std::vector<__int64> CounterStartTimeVector;
		std::vector<double> CounterMinTimeVector;
		std::vector<double> CounterMaxTimeVector;
		std::vector<int>  CounterLoopVector;

	};
	inline FPSCounter::FPSCounter()
		:	mPCFreq(0.0f)
		,	CounterStart(0)
		, CounterStartTimeVector(20)
		, CounterLoopVector(20)
		, CounterMinTimeVector(20)
		, CounterMaxTimeVector(20)
		
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			exit(0);
		mPCFreq = double(li.QuadPart);//miliseconds
		for (std::vector<double>::iterator it = CounterMinTimeVector.begin(); it < CounterMinTimeVector.end(); it++)
		{
			*it = 99999.0f;
		}
		for (std::vector<double>::iterator it = CounterMaxTimeVector.begin(); it != CounterMaxTimeVector.end(); it++)
		{
			*it = -11111.0f;
		}
	}

	inline void FPSCounter::ResetTimeCounter(int counterIdx)
	{
		CounterStartTimeVector[counterIdx] = 0;
		CounterMinTimeVector[counterIdx] = 99999.0f;
		CounterMaxTimeVector[counterIdx] = -11111.0f;
	}

	inline void	FPSCounter::StartTimeCounter(int counterIdx)
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		CounterStartTimeVector[counterIdx] = li.QuadPart;
	}

	inline double FPSCounter::GetTimerCounter(int counterIdx)
	{
		LARGE_INTEGER li;
		QueryPerformanceCounter(&li);
		double counter = double(li.QuadPart - CounterStartTimeVector[counterIdx]) / mPCFreq;//mili
		if (CounterMinTimeVector[counterIdx] > counter)
			CounterMinTimeVector[counterIdx] = counter;
		if (CounterMaxTimeVector[counterIdx] < counter)
			CounterMaxTimeVector[counterIdx] = counter;
		return counter;
	}

	inline double  FPSCounter::GetMaxTimeCounter(int counterIdx)
	{
		return CounterMaxTimeVector[counterIdx];
	}

	inline double  FPSCounter::GetMinTimeCounter(int counterIdx)
	{
		return CounterMinTimeVector[counterIdx];
	}

	inline void FPSCounter::StartLoopCounter(int counterIdx)
	{
		CounterLoopVector[counterIdx] = 0;
	}

	inline int	FPSCounter::GetLoopCounter(int counterIdx)
	{
		return CounterLoopVector[counterIdx];
	}

	inline void	FPSCounter::IncreaseLoopCounter(int counterIdx)
	{
		CounterLoopVector[counterIdx] += 1;
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

		return counter;
	}


}

#endif