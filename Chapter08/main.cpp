#include <iostream>
#include "Calculator.h"

using namespace std;

//*******************************************************

void FirstLine(const string& name) {
	cout << "\n*" << name << "*" << endl;
}

void LastLine() {
	cout << "----------------------------------\n";
}

void Exercise01() {

	FirstLine("Exercise 04");

	Calculator::TokenStream tokenStream(cin);
	cout << "Exercises\n"
	        "Enter an expression followed by a semicolon (ex.: 4!;):" << "\n";
	cout << Calculator::prompt;

	Calculator::Calculate(tokenStream);

	LastLine();
}

int main() {
	cout << "Hello, Chapter 08!" << endl;

	Exercise01();



	return 0;
}