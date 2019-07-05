#pragma once
#include <ctime>

class Time
{
private:
	clock_t _now;
	clock_t _basePeriod;
public:
	Time() : _now(0), _basePeriod(0) {}
	~Time();
public:
	int DeltaTime() { return (_now - _basePeriod) / 1000; }  // delta time
	void SetBasePeriod() { _basePeriod = _now; }	// set base period for delta time
	int NowTime() { return _now / 1000; }  // now time from start
};

