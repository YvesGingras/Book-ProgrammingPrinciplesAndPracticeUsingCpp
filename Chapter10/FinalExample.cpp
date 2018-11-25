/*
 * Created by Yves Gingras on 2018-11-22.
 *
 * The chapter 10 final example, as presented from section '10.11'.
 */

#include <iostream>
#include <fstream>
#include "FinalExample.h"
#include "Invalid.h"

using namespace std;

namespace Temperatures
{

	/**
	 * @brief Read a temperature reading from 'inStream' into 'reading'.
	 *
	 * Recognized Format: '(3 4 9.7)' which stands for: ('day of the month' 'hour of the day' 'temperature).
	 */
	istream& operator>>(istream& inStream, Reading& reading) {
		char char1{}, char2{};

		if (inStream >> char1 &&
		    char1 != '(') { //did'nt find '(' or reached 'eof'. Manage stream and return it to caller...
			inStream.unget();
			inStream.clear(ios_base::failbit);
			return inStream;
		}

		//... and try the rest of the reading...
		int day{};
		int hour{};
		double temperature{};
		inStream >> day >> hour >> temperature >> char2;

		/*Individual testing of a 'temperatures' only file. ('Final Example' section in main.cpp).*/
		if (Temperatures::isTestingMode)
			if (!inStream) // in this case, equivalent to 'if (inStream.eof())'
				return inStream;

		if (!inStream || char2 != ')')
			throw Invalid("\noperator>>(istream,Reading)\n" //... definitely bad.
			              "Error: Bad reading.");

		reading.day = day;
		reading.hour = hour;
		reading.temperature = temperature;

		return inStream;
	}

	/**
	 * @brief Read a Month from 'inStream' into 'month'.
	 *
	 * Recognized format: '{month feb...}
	 */
	std::istream& operator>>(std::istream& inStream, Temperatures::Month& month) {
		char input{};

		if (inStream >> input &&
		    input != '{') { //did'nt find '{' or reached 'eof'. Manage stream and return it to caller...
			inStream.unget();
			inStream.clear(ios_base::failbit);
			return inStream;
		}

		string monthMarker{};
		string monthInput{};
		inStream >> monthMarker >> monthInput;

		/*Individual testing of 'month's only file ('Final Example' section in main.cpp) .*/
		if (Temperatures::isTestingMode)
			if (!inStream) // in this case, equivalent to 'if (inStream.eof())'
				return inStream;

		if (!inStream || monthMarker != "month")
			throw Invalid("\noperator>>(istream,Month\n"
			        "Error: bad start of 'month'.\n");

		int duplicates{};
		int invalids{};
		month.month = MonthToInt(monthInput);

		for (Reading reading; inStream >> reading;) {
			if (IsValid(reading)) {
				if (month.days[reading.day].hours[reading.hour] != notAReading)
					++duplicates;

				month.days[reading.day].hours[reading.hour] = reading.temperature;
			} else
				++invalids;
		}

		if (invalids)
			throw Invalid("operator>>(istream, Month\n"
			              "Error: Invalid 'reading'.");

		if (duplicates)
			throw Invalid("operator>>(istream, Month\n"
			              "Error: Duplicate 'reading's.");

		EndOfLoop(inStream, '}', "operator>>(istream, Month\n"
		                         "Error: Bad 'end of month'.");

		return inStream;
	}

	/**
	 * @brief Read a Year from 'inStream' into 'year'.
	 *
	 * Recognized format: '{year 1972...}
	 */
	std::istream& operator>>(std::istream& inStream, Temperatures::Year& year) {
		char input{};
		inStream >> input;

		if (input != '{') { //did'nt find '{' or reached 'eof'. Manage stream and return it to caller...
			inStream.unget();
			inStream.clear(ios_base::failbit);
			return inStream;
		}

		string yearMarker{};
		int yearInput{};
		inStream >> yearMarker >> yearInput;

		/*Individual testing of 'month's only file ('Final Example' section in main.cpp) .*/
		if (isTestingMode)
			if (!inStream) // in this case, equivalent to 'if (inStream.eof())'
				return inStream;

		if (!inStream || yearMarker != "year")
			throw Invalid("\noperator>>(istream,Year\n"
			        "Error: bad start of 'year'.\n");

		year.year = yearInput;

		while (true) {
			Month month;
			if (!(inStream >> month))
				break;
			year.months[month.month] = month;
		}

		EndOfLoop(inStream, '}', "operator>>(istream, Year\n"
		                         "Error: Bad 'end of year'.");

		return inStream;
	}

	void EndOfLoop(istream& inStream, char terminator, std::string errorMessage) {
		if (inStream.fail()) {
			inStream.clear();
			char input{};

			if (inStream >> input && input == terminator)
				return;

			throw Invalid("EndOfLoop()\n" + errorMessage);
		}
	}

	int MonthToInt(string month) {
		for (int i = 0; i < 12; ++i)
			if (monthInputTable[i] == month)
				return i;

		return notAMonth;
	}

	bool IsValid(const Reading& reading) {
		if (reading.day < 1 || 31 < reading.day)
			return false;

		if (reading.hour < 0 || 23 < reading.hour)
			return false;

		if (reading.temperature < implausibleMin || implausibleMax < reading.temperature)
			return false;

		return true;
	}
}