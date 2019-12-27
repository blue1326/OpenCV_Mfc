//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
// Converted RagNa 2019 All Rights Reserved.
//***************************************************************************************


#ifndef Timer_h__
#define Timer_h__
#include <memory>


typedef __int64 HINT;
class _declspec(dllexport) CTimer
{
public:
	CTimer();
	virtual ~CTimer();
public:


	float TotalTime()const; //seconds
	float DeltaTime()const; //seconds

	void Reset(); //Call before message loop
	void Start(); //Call When unpaused
	void Stop(); //Call when paused
	void Tick(); //Call every frames
	static shared_ptr<CTimer> CreateTimer();
private:
	double m_SecondsPerCount;
	double m_DeltaTime;
	HINT m_BaseTime;
	HINT m_PausedTime;
	HINT m_StopTime;
	HINT m_PrevTime;
	HINT m_CurrTime;

	bool m_Stopped;
};

#endif // Timer_h__
