/*
 * Created by Yves Gingras on 2018-11-14.
 */

#ifndef CHAPTER09_CHRONO_H
#define CHAPTER09_CHRONO_H

#include <string>
#include <istream>

namespace Chrono
{

	enum class Month {
		January = 1,
		February,
		Marsh,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

	class Invalid {

	public:
		Invalid(const std::string& errorMessage);
		std::string m_errorMessage{};
	};

	class Date {
	public:


		Date();
		Date(int year, Month month, int day);

		int GetDay() const { return m_day; }
		Month GetMonth() const { return m_month; }
		int GetYear() const { return m_year; }

		void AddDay(int dayIncrease) ;
		void AddMonth(int monthIncrease);
		void AddYear(int yearIncrease);

	private:
		int m_year{};
		Month m_month{};
		int m_day{};
	};

	Month IntToMonth(int monthValue);
	bool IsDateValid(int year, Month month, int day);
	bool IsDateValid(const Date& date);
	bool IsLeapYear(int year);
	bool operator==(const Date& leftValue, const Date& rightValue);
	bool operator!=(const Date& leftValue, const Date& rightValue);
	std::ostream& operator<<(std::ostream& outStream, const Date& date);
	std::istream& operator>>(std::istream& inStream, Date& date);
	Date DayOfWeek(const Date& day);
	Date NextSunday(const Date& day);
	Date NextWeekend(const Date& day);

}/*namespace Chrono*/





#endif //CHAPTER09_CHRONO_H
