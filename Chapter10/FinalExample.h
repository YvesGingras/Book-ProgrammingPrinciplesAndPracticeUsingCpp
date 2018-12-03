/*
 * Created by Yves Gingras on 2018-11-22.
 *
 * The chapter 10 final example, as presented from section '10.11'.
 */

#ifndef CHAPTER10_FINALEXAMPLE_H
#define CHAPTER10_FINALEXAMPLE_H

#include <vector>
#include <string>

namespace Temperatures
{
	constexpr bool isTestingMode {false};
	constexpr int notAReading{-7777};
	constexpr int notAMonth{-1};
	constexpr int hoursInDay {24};
	constexpr int daysInMonth {32};
	constexpr int monthsInYear {12};
	constexpr int implausibleMin {-200};
	constexpr int implausibleMax {200};
	const std::vector<std::string> monthInputTable {
		"jan", "feb", "mar", "apr", "may", "jun",
		"jul", "aug", "sep", "oct", "nov", "dec" };

	struct Day {
		std::vector<double> hours {std::vector<double>(hoursInDay,notAReading)};
	};

	struct Month {
		int month {notAMonth};
		std::vector<Day> days {daysInMonth};
	};

	struct Year {
		int year{};
		std::vector<Temperatures::Month> months {monthsInYear};
	};

	struct Reading {
		int day {};
		int hour {};
		double temperature {};
	};

	std::istream& operator>>(std::istream& inStream, Reading& reading);
	std::istream& operator>>(std::istream& inStream, Month& month);
	std::istream& operator>>(std::istream& inStream, Year&  year);

	std::vector<Temperatures::Reading> TemperaturesReading(std::ifstream& inStringFile);
	std::vector<Temperatures::Month> MonthsReading(std::ifstream& inStringFile);
	std::vector<Temperatures::Year> YearsReading(std::ifstream& inSteamFile);
	void PrintTemperaturesData(const std::vector<Temperatures::Year>& years);

	void EndOfLoop(std::istream& inStream, char terminator, std::string errorMessage);
	int MonthToInt(std::string month);
	bool IsValid(const Reading& reading);
}/*namespace Temperatures*/

#endif //CHAPTER10_FINALEXAMPLE_H
