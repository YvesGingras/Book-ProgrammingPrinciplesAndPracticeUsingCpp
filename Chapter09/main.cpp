#include <iostream>
#include <vector>
#include "Drill.h"
#include "NamePairs.h"


using namespace std;

//*******************************************************

void FirstLine(const string& name) {
	cout << "\n*" << name << "*" << endl;
}

void LastLine() {
	cout << "----------------------------------\n";
}

void RunVersion9_4_1() {

	try {
		FirstLine("RunVersion9_4_1()");
		Version9_4_1::Date today{};
		Version9_4_1::Date tomorrow{};
		Version9_4_1::InitializeDay(today,1978,6,25);

		tomorrow = today;
		Version9_4_1::AddDay(tomorrow,1);

		cout << "Today's date is: " << today.y << ',' << today.m << ',' << today.d << ".\n";
		cout << "Tomorrow will then be: " << tomorrow.y << ',' << tomorrow.m << ',' << tomorrow.d << ".\n";

		LastLine();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
		                    "Program is terminating...");
	}
}

void RunVersion9_4_2() {

	try {
		FirstLine("RunVersion9_4_2()");
		Version9_4_2::Date today{1978, 6, 25};
		Version9_4_2::Date tomorrow{1900, 01, 01};

		tomorrow = today;
		tomorrow.AddDay(tomorrow,1);

		cout << "Today's date is: " << today.y << ',' << today.m << ',' << today.d << ".\n";
		cout << "Tomorrow will then be: " << tomorrow.y << ',' << tomorrow.m << ',' << tomorrow.d << ".\n";

		LastLine();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
		                    "Program is terminating...");
	}
}

void RunVersion9_4_3() {

	try {
		FirstLine("RunVersion9_4_3()");
		Version9_4_3::Date today{1978, 6, 25};
		Version9_4_3::Date tomorrow{1900, 01, 01};

		tomorrow = today;
		tomorrow.AddDay(tomorrow,1);

		cout << "Today's date is: " << today.GetYear() << ',' << today.GetMonth() << ',' << today.GetDay() << ".\n";
		cout << "Tomorrow will then be: " << tomorrow.GetYear() << ',' << tomorrow.GetMonth() << ','
				<< tomorrow.GetDay() << ".\n";


		LastLine();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
		                    "Program is terminating...");
	}
}

void RunVersion9_7_1() {
	using namespace Version9_7_1;

	try {
		FirstLine("RunVersion9_7_1()");
		Date today{Year{2005},Month::June,25};
		Date tomorrow{Year{1900},Month::January, 01};

		tomorrow = today;
		tomorrow.AddDay(tomorrow,1);

		cout << "Today's date is: " << today.GetYear() << ',' << int(today.GetMonth()) << ',' << today.GetDay() << ".\n";
		cout << "Tomorrow will then be: " << tomorrow.GetYear() << ',' << int(tomorrow.GetMonth()) << ','
		     << tomorrow.GetDay() << ".\n";

		LastLine();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (Invalid& invalid) {
		throw runtime_error(invalid.m_errorMessage);
	}

	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
		                    "Program is terminating...");
	}
}

void RunVersion9_7_4() {
	using namespace Version9_7_4;

	try {
		FirstLine("RunVersion9_7_4()");
		Date today{Year{2005},Month::June,25};
		Date tomorrow{Year{1900},Month::January, 01};

		tomorrow = today;
		tomorrow.AddDay(tomorrow,1);

		cout << "Today's date is: " << today.GetYear() << ',' << int(today.GetMonth()) << ',' << today.GetDay() << ".\n";
		cout << "Tomorrow will then be " << tomorrow << endl;


		tomorrow.AddYear(tomorrow,1);
		tomorrow.AddMonth(tomorrow,1);
		tomorrow.AddDay(tomorrow,1);
		cout << "A day and a month later next year will be " << tomorrow << endl;

		cout << "Testing  default constructor" << '\n';
		vector<Date> dates(10);
		for (int i = 0; i < dates.size(); ++i) {
			cout << "Date " << to_string(i + 1) << ": " << dates[i];
		}

		LastLine();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (Invalid& invalid) {
		throw runtime_error(invalid.m_errorMessage);
	}

	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
		                    "Program is terminating...");
	}
}

void Exercises3To4() {
	using NamePair::NamePairs;

	FirstLine("Exercise3To4()");

	NamePairs namePairs1{};
	namePairs1.ReadNames();
//	namePairs1.Print();

	NamePairs namePairs2{};
	namePairs2.ReadNames();

	cout << "\n*namePairs1*";
	cout << namePairs1;

	cout << "\n*namePairs2*";
	cout << namePairs2;


	cout << boolalpha;
	cout << "\nboolean operators testing\n";
	cout << "namePairs1 == namePairs2: " << (namePairs1 == namePairs2) << '\n';
	cout << "namePairs1 != namePairs2: " << (namePairs1 != namePairs2) << '\n';

	LastLine();
}

int main() {
	cout << "Hello, Chapter 09!" << endl;

	try {
//		RunVersion9_4_1();
//		RunVersion9_4_2();
//		RunVersion9_4_3();
//		RunVersion9_7_1();
//		RunVersion9_7_4();
		Exercises3To4();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		cerr << exceptionWhat;
	}

	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'Main()'!\n"
		                    "Program is terminating...");
	}
	return 0;
}

