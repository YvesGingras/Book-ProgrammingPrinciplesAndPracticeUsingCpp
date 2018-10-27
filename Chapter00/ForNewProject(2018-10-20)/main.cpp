#include <iostream>
#include "Declarations.h"

using namespace std;

int main() {
	cout << "Hello, Chapter 06!\n" << endl;

	try
	{
		cout << ""; //delete line
		/*TryThis*/


		/*Drill*/


		/*Exercises*/


		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << endl;

		return 1;
	}
}


//Definitions
/*Various*/
void FirstLine(const string& name) {
	cout << "\n*" << name << "*";
}

void LastLine() {
	cout << "----------------------------------\n";
}
