#pragma once

#include <ctime>
#include <chrono>
using namespace std::chrono;

class Time
{
private:
	system_clock _time;
	time_point<system_clock> _gamestart;
	time_point<system_clock> _startPeriod;
	time_point<system_clock> _endPeriod;
public:
	Time() { _gamestart = _time.now(); _startPeriod = _time.now(); }
public:
	int DeltaTime() {	// delta time
		_endPeriod = _time.now();
		duration<double> deltaTime = _endPeriod - _startPeriod;
		return static_cast<int>(deltaTime.count());
	}
	void SetBasePeriod() { _startPeriod = _time.now(); }	// set base period for delta time
	int NowTime() {		// now time from start
		_endPeriod = _time.now();
		duration<double> deltaTime = _endPeriod - _gamestart;
		return static_cast<int>(deltaTime.count());
	}  
};

