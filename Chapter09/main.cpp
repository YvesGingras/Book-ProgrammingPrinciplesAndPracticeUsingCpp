#include <iostream>
#include <vector>
#include "Drill.h"
#include "Chrono.h"
#include "NamePairs.h"
#include "Library/Book.h"
#include "Library/Patron.h"

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

/*
		cout << "Testing  default constructor" << '\n';
		vector<Date> dates(10);
		for (int i = 0; i < dates.size(); ++i) {
			cout << "Date " << to_string(i + 1) << ": " << dates[i];
		}
*/

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

void RunVersionChrono() {
	using namespace Chrono;

	try {
		FirstLine("RunVersionChrono'9.8'");
		Date today{1978,Month::June,25};
		Date tomorrow{};

		tomorrow = today;
		tomorrow.AddDay(1);

		cout << "Today's date is: " << today.GetYear() << ',' << int(today.GetMonth()) << ',' << today.GetDay() << ".\n";
		cout << "Tomorrow will then be " << tomorrow << endl;

		tomorrow.AddYear(1);
		tomorrow.AddMonth(1);
		tomorrow.AddDay(1);
	cout << "A day and a month later next year will be " << tomorrow << endl;

//		cout << "Testing  default constructor" << '\n';
//		vector<Date> dates(10);
//		for (int i = 0; i < dates.size(); ++i) {
//			cout << "Date " << to_string(i + 1) << ": " << dates[i];
//		}

		cout << "\nTesting  '>>' operator." << '\n';
		Date testInStream{};
		cout << "Enter date '(yyyy,mm,dd)': \n";
		cin >> testInStream;
		cout << "testInStream: " << testInStream << endl;

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

// Exercises 5 to 9 (Library project).
void TestingBookClass(vector<Library::Book> books);
void TestingPatronClass(vector<Library::Patron> patrons);

void RunLibraryProject(){
	using namespace Library;

	/******Testing books - Begin*/
	FirstLine("RunLibraryProject()");
	Book book1{};
	Book book2{
			"Royal Assassin",
			"Robin Hobb",
			"978-2-290-08599-8",
			Chrono::Date{1995, Chrono::Month::November, 20},
			Genre::Fiction,
			false};

	Book book3{book2};

	vector<Book> books {book1, book2, book3};
	TestingBookClass(books);
	/******Testing books - End*/


	/******Testing patrons - Begin*/
	Patron patron1{};
	Patron patron2{1234,12.5};

	vector<Patron> patrons {patron1, patron2};
	TestingPatronClass(patrons);
	/******Testing patrons - End*/


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
//		Exercises3To4();
//		RunVersionChrono();
		RunLibraryProject();
	}
	catch (Library::Invalid& e) {
		auto exceptionWhat{string(e.m_errorMessage)};
		cerr << exceptionWhat;
	}

	catch (Chrono::Invalid& e) {
		auto exceptionWhat{string(e.m_errorMessage)};
		cerr << exceptionWhat;
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

void TestingBookClass(vector<Library::Book> books) {
	auto book1 = books[0];
	auto book2 = books[1];
	auto book3 = books[2];


	cout << boolalpha;

	cout << "\nBook1";
	cout << book1 << endl;

	book2.CheckOut();
	cout << "\nBook2";
	cout << book2 << endl;

	book2.CheckIn();
	cout << "\nBook2";
	cout << book2 << endl;

	book2.CheckOut();
	cout << "\nBook2";
	cout << book2 << endl;

	cout << "\nBook3";
	cout << book3 << endl;

	cout << "\nBook equality operators.";
	cout << "\nbook3 == book2: " << (book3 == book2) << endl;
	cout << "book3 != book2: " << (book3 != book2) << endl;

	cout << "\nbook1 == book2: " << (book1 == book2) << endl;
	cout << "book1 != book2: " << (book1 != book2) << endl;


}

void TestingPatronClass(vector<Library::Patron> patrons) {
	auto patron1 = patrons[0];
	auto patron2 = patrons[1];

	cout << boolalpha;

	cout << "\nPatron1";
	cout << patron1 << endl;

	cout << "\nPatron2";
	cout << patron2 << endl;
	cout << "Fee to pay? " << IsLateFee(patron2) << endl;
	patron2.SetLateFee(0);
	cout << patron2 << endl;
	cout << "Fee to pay? " << IsLateFee(patron2) << endl;
}