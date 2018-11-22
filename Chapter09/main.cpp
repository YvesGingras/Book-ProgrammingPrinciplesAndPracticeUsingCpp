#include <iostream>
#include <vector>
#include "Drill.h"
#include "Chrono.h"
#include "NamePairs.h"
#include "Library/Book.h"
#include "Library/Patron.h"
#include "Library/Library.h"

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

// Exercises 5 to 9 (Learning project).
void TestingBookClass(vector<Learning::Book> books);
void TestingPatronClass(vector<Learning::Patron>& patrons);
std::vector<Learning::Book> CreateBooks();

void RunLibraryProject(){
	using namespace Learning;

	FirstLine("RunLibraryProject()");

	Chrono::Date checkOutDate {2018, Chrono::Month::November,21};

	/******Testing books - Begin*/
	vector<Book> books =  CreateBooks();;
	TestingBookClass(books);
	Book phonyBook {"Phony book","nobody","1-2-3-4-5",checkOutDate,Genre::ToDefine,false};
	/******Testing books - End*/

	/******Testing patrons - Begin*/
	Patron patron1{};
	Patron patron2{2,12.5};
	Patron patron3{3,1.5};
	Patron patron4{4,0};
	Patron patron5{5,5.75};
	Patron phonyPatron {999999,0};


	vector<Patron> patrons {patron1, patron2, patron3, patron4, patron5};
	TestingPatronClass(patrons); //todo: somehow deal with '* and &' (??) to bring modification back to caller.
	/******Testing patrons - End*/

	/******Testing Library - Begin*/
	Library library;
	library.AddBook(books[0]);
	library.AddBook(books[1]);
	library.AddBook(books[3]);
	library.AddBook(books[4]);

	library.AddPatron(patron1);
	library.AddPatron(patron2); // todo: should bring back 'LateFee' at the value set in 'TestingPatronClass()' method.
	library.AddPatron(patron3);
	library.AddPatron(patron4);
	library.AddPatron(patron5);

//	library.CheckOutBook(patron2,books[1], checkOutDate); /*error ows a fee.*/
//	library.CheckOutBook(patron4,phonyBook, checkOutDate); /*error book not present.*/
//	library.CheckOutBook(phonyPatron,books[1], checkOutDate); /*error user not present.*/
	library.CheckOutBook(patron4,books[1], checkOutDate);


	//Continue: Create 'TestingLibraryClass'
	cout << "\nLibrary ******************************";
	library.DisplayIndebtedPatrons();


	cout << "";

	/******Testing Library - End*/

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
	catch (Learning::Invalid& e) {
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

//utility
void TestingBookClass(vector<Learning::Book> books) {
	auto book1 = books[0];
	auto book2 = books[1];
	auto book3 = books[2];


	cout << boolalpha;

	cout << "\nBook ******************************";
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

void TestingPatronClass(vector<Learning::Patron>& patrons) {
	auto patron1 = patrons[0];
	auto patron2 = patrons[1];
	auto patron3 = patrons[2];
	auto patron4 = patrons[3];

	cout << boolalpha;
	cout << "\nPatron ******************************";

	cout << "\nPatron1";
	cout << patron1 << endl;

	cout << "\nPatron2";
	cout << patron2 << endl;
	cout << "Fee to pay? " << IsLateFee(patron2) << endl;
	patron2.SetLateFee(500); //
	cout << patron2 << endl;
	cout << "Fee to pay? " << IsLateFee(patron2) << endl;

	cout << "\nPatron3";
	cout << patron3 << endl;
	cout << "Fee to pay? " << IsLateFee(patron3) << endl;

	cout << "\nPatron4";
	cout << patron4 << endl;
	cout << "Fee to pay? " << IsLateFee(patron4) << endl;
}

std::vector<Learning::Book> CreateBooks() {
	using namespace Learning;
	Learning::Book book1{};
	Learning::Book book2{
			"Royal Assassin",
			"Robin Hobb",
			"978-2-290-08599-8",
			Chrono::Date{1995, Chrono::Month::November, 20},
			Learning::Genre::Fiction,
			false};

	Learning::Book book3{book2};

	Learning::Book book4{
			"Programming: Principles and Practice Using C++",
			"Bjarne Stroustrup",
			"978-0-321-99278-9",
			Chrono::Date{2018, Chrono::Month::January, 01},
			Learning::Genre::NonFiction,
			false};

	Learning::Book book5{
			"Effective Modern C++",
			"Scott Meyers",
			"978-1-491-90399-5",
			Chrono::Date{2015, Chrono::Month::January, 01},
			Learning::Genre::NonFiction,
			false};

	return vector<Book>  {book1, book2, book3, book4, book5};

}
