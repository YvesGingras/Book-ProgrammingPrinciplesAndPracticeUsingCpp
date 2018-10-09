//
// Created by Yves Gingras on 2018-10-07.
//

#ifndef CHAPTER03_EXAMPLE_H
#define CHAPTER03_EXAMPLE_H

#include "std_lib_facilities.h"
#include "Utilities.h"

 //read name and age
/** @brief read name and age */
void Example3_3First() {
	FirstLine("Example3_3First()");
	cout << "please enter your first name and age\n";
	string first_name;  // string variable
	int age;            // integer variable
	cin >> first_name;  // read a string
	cin >> age;         // read an integer
	cout << "Hello, " << first_name << " (age " << age << ")\n";
	LastLine();
}

//read name and age (2nd version)
void Example3_3Second() {
	FirstLine("Example3_3Second()");

	cout << "please enter your first_name and age\n";
	string first_name = "???";  // string variable
								// ("???" means "don't know the name")

	int age = 0;               // integer variable (-1 means "don't know the age")
	cin >> first_name >> age;   // read a string followed by an integer
	cout << "Hello, " << first_name << " (age " << age << ")\n";

	LastLine();
}

//simple program to exercise operators
void Example3_4Float() {
	FirstLine("Example3_4Float()");

	cout << "please enter a floating-point value: ";
	double n;
	cin >> n;
	cout << "n == " << n
	     << "\nn+1 == " << n+1
	     << "\nthree times n == " << 3*n
	     << "\ntwice n == " << n+n
	     << "\nn squared == " << n*n
	     << "\nhalf of n == " << n/2
	     << "\nsquare root of n == " << sqrt(n)
	     << endl; // another name for newline ("end of line")

	LastLine();
}

// read and compare names:
void Example3_4Compare() {
	FirstLine("Example3_4Compare()");

	cout << "please enter two names\n";
	string first;
	string second;

	cin >> first >> second; // read two strings

	if (first == second) cout << "that's the same name twice\n";

	if (first < second)
		cout << first << " is alphabetically before " << second <<'\n';

	if (first > second)
		cout << first << " is alphabetically after " << second <<'\n';

	LastLine();
}

/** @brief Empty Template Method */
 void Example3_5_1() {
	FirstLine("Example3_5_1()");

	string previous = " ";       // not a word
	string current;

	while (cin>>current) {       // read a stream of words
		if (previous == current) // check if the word is the same as last
			cout << "repeated word: " << current << '\n';
		previous = current;
	}

	LastLine();
}

/** @brief Safe conversions*/
void Example3_9_1() {
	FirstLine("Example3_9_1()");

	char c = 'x';
	int i1 = c;
	int i2 = 'x';
	char c2 = i1;

	cout << c << ' ' << i1 << ' ' << c2 << '\n'; // This will print: x 120 x

	double d1 = 2.3;
	double d2 = d1+2; // 2 is converted to 2.0 before adding

	if (d1 < 0)       // 0 is converted to 0.0 before comparison
		error("d1 is negative");

	LastLine();
}

/** @brief This is example code from Chapter 3.9.2 "Unsafe conversions"*/
void Example3_9_2First() {
	FirstLine("Example3_9_2First()");

	int a = 2000;
	char c = a; // try to squeeze a large int into a small char
	int b = c;
	if (a != b) // != means "not equal"
		cout << "oops!: " << a << "!=" << b << '\n';
	else
		cout << "Wow! We have large characters\n";

	LastLine();
}

/** @brief This is example code from Chapter 3.9.2 "Unsafe conversions"*/
void Example3_9_2Second() {
	FirstLine("Example3_9_2Second()");

	double d =0;
	while (cin>>d) {   // repeat the statements below
		// as long as we type in numbers
		int i = d;     // try to squeeze a double into an int
		char c = i;    // try to squeeze an int into a char
		int i2 = c;    // get the integer value of the character

		cout << "d==" << d              // the original double
		     << " i=="<< i              // converted to int
		     << " i2==" << i2           // int value of char
		     << " char(" << c << ")\n"; // the char
	}

	double x = 2.7;
	// lots of code
	int y = x;         // y becomes 2
	int a = 1000;
	char b = a;        // b becomes -24 (on some machines)

	LastLine();
}

#endif //CHAPTER03_EXAMPLE_H
