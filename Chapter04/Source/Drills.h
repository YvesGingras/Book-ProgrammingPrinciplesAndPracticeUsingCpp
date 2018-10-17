//
// Created by Yves Gingras on 2018-10-06.
//

#ifndef CHAPTER04_DRILLS_H
#define CHAPTER04_DRILLS_H

//#include "std_lib_facilities.h"
#include "Utilities.h"

void DrillChapter04Pg149();

/** @brief Writes a program that consists of a while-loop that (each time around the loop)
 * reads in two ints and then prints them. Exit the program when a terminating '|' is entered.
 */
void DrillChapter04Pg149() {
	FirstLine("DrillChapter04Pg149()");

	string controlValue{"ok"};

	//Step 1
	/*
	while (controlValue != "|") {
		int value1{};
		int value2{};

		if (cin >> value1) {
			cin >> value2;
			cout << "Value 1: " << value1 << " Value 2: " << value2 << endl;
			cout << "\nEnter 2 integer value or '|' to terminate:" << endl;
		} else
			controlValue = "|";

		LastLine();
	}
	*/

	//Step 2
	/*
	while (controlValue != "|") {
		int value1{};
		int value2{};

		if (cin >> value1) {
			cin >> value2;
			if (value1 < value2)
				cout << "\nThe smaller value is : " << value1
					 << "\nThe larger value is : " << value2 << endl;
			else
				cout << "\nThe smaller value is : " << value2
				     << "\nThe larger value is : " << value1 << endl;

			cout << "\nEnter 2 integer value or '|' to terminate:" << endl;
		} else
			controlValue = "|";

		LastLine();
	}
	*/

	//Step 3
	/*
	While (controlValue != "|") {
		int value1{};
		int value2{};

		if (cin >> value1) {
			cin >> value2;
			if (value1 < value2)
				cout << "\nThe smaller value is : " << value1
				     << "\nThe larger value is : " << value2 << endl;
			else if (value1 > value2)
				cout << "\nThe smaller value is : " << value2
				     << "\nThe larger value is : " << value1 << endl;
			else
				cout << "\nThe numbers are equal." << endl;

			cout << "\nEnter 2 integer value or '|' to terminate:" << endl;
		} else
			controlValue = "|";

		LastLine();
	}
	*/

	//Step 4
	/*
	cout << "Enter 2 double values or '|' to terminate: " << endl;
	while (controlValue != "|") {
		double value1{};
		double value2{};

		if (cin >> value1) {
			cin >> value2;
			if (value1 < value2)
				cout << "\nThe smaller value is : " << value1
				     << "\nThe larger value is : " << value2 << endl;
			else if (value1 > value2)
				cout << "\nThe smaller value is : " << value2
				     << "\nThe larger value is : " << value1 << endl;
			else
				cout << "\nThe numbers are equal." << endl;

			cout << "\nEnter 2 double value or '|' to terminate:" << endl;
		} else
			controlValue = "|";

		LastLine();
	}*/

	//Step 5
	/*
	cout << "Enter 2 double values or '|' to terminate: " << endl;
	while (controlValue != "|") {
		double value1{};
		double value2{};

		if (cin >> value1) {
			cin >> value2;
			if (value1 < value2) {
				cout << "\nThe smaller value is : " << value1
				     << "\nThe larger value is : " << value2 << endl;

				if (value2 - value1 < 1.0 / 100)
					cout << "\nThe numbers are almost equal" << endl;
			}
			else if (value1 > value2) {
				cout << "\nThe smaller value is : " << value2
				     << "\nThe larger value is : " << value1 << endl;

				if (value1 - value2 < 1.0 / 100)
					cout << "\nThe numbers are almost equal" << endl;
			}
			else
				cout << "\nThe numbers are equal." << endl;

			cout << "\nEnter 2 double value or '|' to terminate:" << endl;
		} else
			controlValue = "|";
	}
    */

	//Step 6
	/*
	auto smallestValue{0.0};
	auto largestValue{0.0};

	cout << "Enter 1 double values or '|' to terminate: " << endl;
	while (controlValue != "|") {
		double inputValue{};

		if (cin >> inputValue) {
			cout << "\nValue entered: " << inputValue << endl;

			if (inputValue <= smallestValue) {
				smallestValue = inputValue;

				cout << "\nThe smallest value so far." << endl;

			}
			else if (inputValue >= largestValue) {
				largestValue = inputValue;

				cout << "\nThe largest value so far." << endl;
			}

			cout << "\nEnter 1 double value or '|' to terminate:" << endl;
		} else
			controlValue = "|";
	}
	 */

	//step 7
	//Continue: code is copied only from step 6
	double smallestValue{0.0};
	auto largestValue{0.0};

	cout << "Enter 1 double values or '|' to terminate: " << endl;
	while (controlValue != "|") {
		double inputValue{};

		if (cin >> inputValue) {
			cout << "\nValue entered: " << inputValue << endl;

			if (inputValue <= smallestValue) {
				smallestValue = inputValue;

				cout << "\nThe smallest value so far." << endl;

			}
			else if (inputValue >= largestValue) {
				largestValue = inputValue;

				cout << "\nThe largest value so far." << endl;
			}

			cout << "\nEnter 1 double value or '|' to terminate:" << endl;
		}
		else{
			controlValue = "|";
			cout << "Bye!" << endl;
		}
	}

	LastLine();

}






#endif //CHAPTER04_DRILLS_H
