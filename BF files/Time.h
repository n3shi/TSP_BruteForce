#include <chrono>
#include <string>
#pragma once
using namespace std::chrono;
class Time {
public:
	high_resolution_clock::time_point timeStart;
	high_resolution_clock::time_point timeStop;

	void TimeStart();
	void TimeStop();
	long CountTime();
};