/*
 * Created by Yves Gingras on 2018-11-14.
 */

#include <iostream>
#include "Chrono.h"

using namespace std;

namespace Chrono
{
	const Date& DefaultDate() {
		static Date defaultDate {Date {2001, Month::January, 01}};
		return defaultDate;
	}

	Date::Date()
		: m_year(DefaultDate().GetYear()),
		  m_month(DefaultDate().GetMonth()),
		  m_day(DefaultDate().GetDay()){ }

	Date::Date(int year, Month month, int day)
			: m_year(year), m_month(month), m_day(day) {
		if (!IsDateValid(year,month,day))
			throw Invalid("Date(int,Month,int)\n"
				 "Error: Invalid date '"
				 + to_string(year) + ","
				 + to_string(int(month)) + ","
				 + to_string(day) + "'\n");
	}

	void Date::AddDay(int dayIncrease) {
		m_day += dayIncrease;
		if (m_day < 1 || m_day > 31)
			throw Invalid("VersionChrono::AddDay()\n"
				 "Error: Day value must be in range 1:31");
	}

	void Date::AddMonth(int monthIncrease) {
		try {
			auto monthValue { (int(m_month) + monthIncrease) };
			m_month = IntToMonth(monthValue); //throws runtime_error if illegal
		}
		catch (Invalid& e) {
			auto exceptionWhat{(e.m_errorMessage)};
			throw Invalid(exceptionWhat);
		}
	}

	void Date::AddYear(int yearIncrease) {
		if (m_month == Month::February && m_day == 29 && IsLeapYear(m_year + yearIncrease)){
			m_month = Month::Marsh;
			m_day = 1;
		}
		m_year += yearIncrease;
	}

	Invalid::Invalid(const string& errorMessage)
		: m_errorMessage(errorMessage){	}

	//helper functions
	bool IsDateValid(int year, Month month, int day) {
		//assume year is valid

		if (day <= 0)
			return false;

		if (month < Month::January || Month::December < month)
			return false;

		int daysInMonth{};
		switch (month) {
			case Month::February:
				daysInMonth = IsLeapYear(year)?29:28;
				break;
			case Month::April:
			case Month::June:
			case Month::September:
			case Month::November:
				daysInMonth = 30;
				break;
			default:
				daysInMonth = 31;
		}
		return daysInMonth >= day;
	}

	bool IsDateValid(const Date& date) {
		int day = date.GetDay();
		Month month = date.GetMonth();

		if (day <= 0)
			return false;

		if (month < Month::January || Month::December < month)
			return false;

		int daysInMonth{};
		switch (month) {
			case Month::February:
				daysInMonth = IsLeapYear(date.GetYear())?29:28;
				break;
			case Month::April:
			case Month::June:
			case Month::September:
			case Month::November:
				daysInMonth = 30;
				break;
			default:
				daysInMonth = 31;
		}
		return daysInMonth >= day;
	}

	bool IsLeapYear(int year) {
		return year % 4 == 0 && year % 400 != 0;
	}

	Month IntToMonth(int monthValue) {
		if (monthValue < int(Month::January) || int(Month::December) < monthValue)
			throw Invalid("IntToMonth()\n"
			                    "Error: Value for month must be between 1 and 12.\nReceived '"
			                    + to_string(monthValue) + "'.");

		return Month(monthValue);
	}

	ostream& operator<<(ostream& outStream, const Date& date) {
		return outStream << '('
		                 << date.GetYear()
		                 << ',' << int(date.GetMonth())
		                 << ',' << date.GetDay()
		                 << ')' << endl;

	}

	std::istream& operator>>(std::istream& inStream, Date& date) {
		int year{}, month{}, day{};
		char char1{}, char2{}, char3{}, char4{};

		inStream >> char1 >> year >> char2 >> month >> char3 >> day >> char4;

		if (!inStream)
			return inStream;

		if (char1!='(' || char2 != ',' || char3 != ',' || char4 != ')') {
			inStream.clear(ios_base::failbit);
			return inStream;
		}

		date = Date { year, Month(month), day };

		return inStream;
	}

	bool operator==(const Date& leftValue, const Date& rightValue) {
		return leftValue.GetYear() == rightValue.GetYear() &&
				leftValue.GetMonth() == rightValue.GetMonth() &&
				leftValue.GetDay() == rightValue.GetDay();
	}

	bool operator!=(const Date& leftValue, const Date& rightValue) {
		return !(leftValue == rightValue);
	}
}/*namespace Chrono*/