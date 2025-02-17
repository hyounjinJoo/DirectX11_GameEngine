#pragma once
#include "hjEngine.h"

namespace hj
{
	class Time
	{
	public:
		static __forceinline float FixedDeltaTime() { return mFixedDeltaTime; }
		static __forceinline float ActualDeltaTime() { return mActualDeltaTime; }

		static __forceinline float AccTime() { return mAccTime; }
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static __forceinline void StopDeltaTimeUpdate(bool stop) { mbStopDeltaTimeUpdate = stop; }
		static __forceinline bool IsStopped() { return mbStopDeltaTimeUpdate; }

	private:
		static LARGE_INTEGER	mCpuFrequency;
		static LARGE_INTEGER	mPrevFrequency;
		static LARGE_INTEGER	mCurFrequency;

		static float			mFixedDeltaTime;
		static float			mActualDeltaTime;
		static float			mAccTime;
		static float			mOneSecond;

		static bool				mbStopDeltaTimeUpdate;
	};
}


