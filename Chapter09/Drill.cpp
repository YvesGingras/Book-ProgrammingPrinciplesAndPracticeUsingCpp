/*
 * Created by Yves Gingras on 2018-11-12.
 */

#include "Drill.h"
#include <stdexcept>

using namespace std;


namespace Version9_4_1
{
	void InitializeDay(Date& date, int year, int month, int day) {
		if(year < 0 || (month < 1 || month > 12) || (day < 1 || day > 31))
			throw runtime_error("Version9_4_1::InitializeDay()\n"
					   "Error: Legal format for day must be '1900,01,01'\n");

		date.y = year;
		date.m = month;
		date.d = day;
	}

	void AddDay(Date& date, int dayIncrease) {
		auto tempDate = date;
		tempDate.d += dayIncrease;

		if (tempDate.d < 1 || tempDate.d > 31)
			throw runtime_error("AddDay()\n"
					   "Error: A 'day' value cannot exceed 31\n");

		date.d = tempDate.d;
	}
} /* namespace Version9_4_1 */

namespace Version9_4_2
{

	Date::Date(int year, int month, int day) {
		if(year < 0 || (month < 1 || month > 12) || (day < 1 || day > 31))
			throw runtime_error("Version9_4_2::Date()\n"
			                    "Error: Legal format for day must be '1900,01,01'\n");

		y = year;
		m = month;
		d = day;
	}

	void Date::AddDay(Date& date, int dayIncrease) {
		auto tempDate = date;
		tempDate.d += dayIncrease;

		if (tempDate.d < 1 || tempDate.d > 31)
			throw runtime_error("Version9_4_2::AddDay()\n"
			                    "Error: A 'day' value cannot exceed 31\n");

		date.d = tempDate.d;
	}
}

namespace Version9_4_3
{
	Date::Date(int year, int month, int day) {
		if(year < 0 || (month < 1 || month > 12) || (day < 1 || day > 31))
			throw runtime_error("Version9_4_3::Date()\n"
			                    "Error: Legal format for day must be '1900,01,01'\n");

		y = year;
		m = month;
		d = day;
	}

	void Date::AddDay(Date& date, int dayIncrease) {
		auto tempDate = date;
		tempDate.d += dayIncrease;

		if (tempDate.d < 1 || tempDate.d > 31)
			throw runtime_error("Version9_4_3::AddDay()\n"
			                    "Error: A 'day' value cannot exceed 31\n");

		date.d = tempDate.d;
	}
}

namespace Version9_7_1
{
	Date::Date(Year year, Month month, int day) {
		if(year.GetYear() < 0 || (int(month) < 1 || int(month) > 12) || (day < 1 || day > 31))
			throw runtime_error("Version9_4_3::Date()\n"
			                    "Error: Legal format for day must be '1900,01,01'\n");

		m_year = year.GetYear();
		m_month = month;
		m_day = day;
	}

	void Date::AddDay(Date& date, int dayIncrease) {
		auto tempDate = date;
		tempDate.m_day += dayIncrease;

		if (tempDate.m_day < 1 || tempDate.m_day > 31)
			throw runtime_error("Version9_4_3::AddDay()\n"
			                    "Error: A 'day' value cannot exceed 31\n");

		date.m_day = tempDate.m_day;
	}

	Year::Year(int year) : m_year(year) {
		if (year < min || max <= year)
			throw Invalid("Year(int year)\n"
				 "Error: Invalid year as input '" + to_string(year) + "'.");
	}

	Invalid::Invalid(const string& errorMessage) : m_errorMessage(errorMessage) { }
}

namespace Version9_7_4
{
	Date::Date(Year year, Month month, int day) {
		if(year.GetYear() < 0 || (int(month) < 1 || int(month) > 12) || (day < 1 || day > 31))
			throw runtime_error("Version9_4_3::Date()\n"
			                    "Error: Legal format for day must be '1900,01,01'\n");

		m_year = year.GetYear();
		m_month = month;
		m_day = day;
	}

	void Date::AddYear(Date& date, int yearIncrease) {
		auto tempDate = date;
		tempDate.m_year += yearIncrease;

		if (tempDate.m_year > Year::GetYearMax())
			throw runtime_error("Version9_7_4::AddYear()\n"
			                    "Error: A 'year' value cannot exceed " + to_string(Year::GetYearMax()) + ".\n");

		date.m_year = tempDate.m_year;
	}

	void Date::AddMonth(Date& date, int monthIncrease) {
		try {
			auto monthValue { (int(date.m_month) + monthIncrease) };
			date.m_month = IntToMonth(monthValue); //throws runtime_error if illegal
		}
		catch (exception& e) {
			auto exceptionWhat{string(e.what())};
			throw runtime_error(exceptionWhat);
		}
	}

	void Date::AddDay(Date& date, int dayIncrease) {
		auto tempDate = date;
		tempDate.m_day += dayIncrease;

		if (tempDate.m_day < 1 || tempDate.m_day > 31)
			throw runtime_error("Version9_4_3::AddDay()\n"
			                    "Error: A 'day' value cannot exceed 31\n");

		date.m_day = tempDate.m_day;
	}

	const Date& Date::DefaultDate() {
		static Date defaultDate {Date {Year{2001}, Month::January, 01}};
		return defaultDate;
	}

	Date::Date()
		: m_year(DefaultDate().GetYear()),
		  m_month(DefaultDate().GetMonth()),
		  m_day(DefaultDate().GetDay()) { }

	Year::Year(int year) : m_year(year) {
		if (year < m_min || m_max <= year)
			throw Invalid("Year(int year)\n"
			              "Error: Invalid year as input '" + to_string(year) + "'.");
	}

	Invalid::Invalid(const string& errorMessage) : m_errorMessage(errorMessage) { }

	Month IntToMonth(int monthValue) {
		if (monthValue < int(Month::January) || int(Month::December) < monthValue)
			throw runtime_error("IntToMonth()\n"
				 "Error: Value for month must be between 1 and 12.\nReceived '" + to_string(monthValue) + "'.");

		return Month(monthValue);
	}

	ostream& operator<<(std::ostream& outStream, Date date) {
		return outStream << '('
						 << date.GetYear()
						 << ',' << int(date.GetMonth())
						 << ',' << date.GetDay()
						 << ')' << endl;
	}
}



