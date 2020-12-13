#include "Time.h"

void Time::TimeStart() // rozpoczecie mierzenia czasu
{
	timeStart = high_resolution_clock::now();
}

void Time::TimeStop() // zakonczenie mierzenia czasu
{
	timeStop = high_resolution_clock::now();
}

long Time::CountTime() // zwraca czas pomiedzy funkcjami czasPoczatkowy i czas Koncowy
{
	return duration_cast<milliseconds>(Time::timeStop - Time::timeStart).count();
}
