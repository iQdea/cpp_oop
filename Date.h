#pragma once
#include <sstream>
#include <iostream>
#include <regex>
#include <ctime>
#include <time.h>
#include <MemoryBuffer.h>

using namespace std;

class Date
{
public:
	static tm toTm(string& date) {
		tm time;

		stringstream ss(date);
		ss >> get_time(&time, "%Y-%m-%d");
		time.tm_hour = 0;
		time.tm_min = 0;
		time.tm_sec = 0;

		return time;
	}
	static time_t toTime(string& date) {
		tm time = toTm(date);
		return mktime(&time);
	}

	static int getDays(string beginDate, string endDate) {
		return (long) (difftime(toTime(endDate), toTime(beginDate)) / 3600 / 24);
	}

	static string firstDayOfNextMonth(string date) {
		tm time = toTm(date);
		time.tm_year += (time.tm_mon == 11) ? 1 : 0;
		time.tm_mon = (time.tm_mon == 11) ? 0 : time.tm_mon + 1;
		time.tm_mday = 1;

		stringstream ss;
		ss << put_time(&time, "%Y-%m-%d");

		return ss.str();
	}
};
