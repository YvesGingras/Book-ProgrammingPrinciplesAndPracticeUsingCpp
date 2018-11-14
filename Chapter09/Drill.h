/*
 * Created by Yves Gingras on 2018-11-12.
 */


//Drill definition
/*
This drill simply involves getting the sequence of versions of Date to work. For each version define a Date called
today initialized to June 25, 1978. Then, define a Date called tomorrow and give it a value by copying today into it
and increasing its day by one using add_day(). Finally, output today and tomorrow using a << defined as in §9.8.

Your check for a valid date may be very simple. Feel free to ignore leap years. However, don’t accept a month that
is not in the [1,12] range or day of the month that is not in the [1,31] range. Test each version with at least one
invalid date (e.g., 2004, 13, –5).

 1. The version from §9.4.1
 2. The version from §9.4.2
 3. The version from §9.4.3
 4. The version from §9.7.1
 5. The version from §9.7.4

 */


#ifndef CHAPTER09_DRILL_H
#define CHAPTER09_DRILL_H

#include <string>
#include <iostream>

namespace Version9_4_1
{
	struct Date{
		int y;
		int m;
		int d;
	};

	void InitializeDay(Date& date, int year, int month, int day);
	void AddDay(Date& date, int dayIncrease);
} /* namespace Version9_4_1 */

namespace Version9_4_2
{
	struct Date{
		int y;
		int m;
		int d;

		Date(int year, int month, int day);
		void AddDay(Date& date, int dayIncrease);
	};
} /* namespace Version9_4_2 */

namespace Version9_4_3
{
	class Date {
	public:
		Date(int year, int month, int day);
		void AddDay(Date& date, int dayIncrease);

		int GetYear() { return y; }
		int GetMonth() {return m; }
		int GetDay() {return d; }
	private:
		int y;
		int m;
		int d;
	};
} /* namespace Version9_4_3 */

namespace Version9_7_1
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

	class Year {
	public:
		Year(int year);
		int GetYear() const {return m_year;}

	private:
		static constexpr int min{1800};
		static constexpr int max{2200};
		int m_year;
	};

	class Date {
	public:
		Date(Year year, Month month, int day);
		void AddDay(Date& date, int dayIncrease);

		int GetYear() const { return m_year; }
		Month GetMonth() const {return m_month; }
		int GetDay() const {return m_day; }

	private:
		int m_year;
		Month m_month;
		int m_day;
	};
}

namespace Version9_7_4
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

	class Year {
	public:
		Year(int year);
		int GetYear() const {return m_year;}
		static int GetYearMax() {return m_max;};

	private:
		static constexpr int m_min{1800};
		static constexpr int m_max{2200};
		int m_year;
	};

	class Date {
	public:
		Date();
		Date(Year year, Month month, int day);
		void AddYear(Date& date, int yearIncrease);
		void AddMonth(Date& date, int monthIncrease);
		void AddDay(Date& date, int dayIncrease);

		int GetYear() const { return m_year; }
		Month GetMonth() const {return m_month; }
		int GetDay() const {return m_day; }

	private:
		int m_year;
		Month m_month;
		int m_day;
		const Date& DefaultDate();

	};

	Month IntToMonth(int monthValue);
	std::ostream& operator<<(std::ostream& outStream, Date date);

}

#endif //CHAPTER09_DRILL_H
