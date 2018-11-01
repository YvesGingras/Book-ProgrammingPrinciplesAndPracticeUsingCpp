#include <iostream>
#include "CalculatorCh06.h"
#include "CalculatorV1.h"
#include "VariousDeclarations.h"

using namespace std;

int main() {
	cout << "Hello, Chapter07!\n" << endl;

	try
	{

//		CalculatorFinalCh06();
		CalculatorVersion1();




		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << endl;

		return 1;
	}


	return 0;
}

//Definitions

void FirstLine(const string& name) {
	cout << "\n*" << name << "*";
}

void LastLine() {
	cout << "----------------------------------\n";
}

void CalculatorFinalCh06() {
	double value = 0;
	CalculatorCh06::TokenStream tokenStream;

	cout << "CalculatorFinalCh06\n"
	        "Enter expression (ex.: 4!;): " << '\n';
	while (cin) {
		CalculatorCh06::Token token = tokenStream.getToken();

		if (token.kind == 'q') break; // 'q' for quit
		if (token.kind == ';')        // ';' for "print now"
			cout << "= " << value << '\n';
		else
			tokenStream.putback(token);
		value = CalculatorCh06::Expression(tokenStream);
	}
}

//VBeginning chapter 7 modification form here.
int CalculatorVersion1() {

	double value = 0;
	CalculatorV1::TokenStream tokenStream;

	cout << "CalculatorVersion1\n"
	        "Enter an expression followed by a semicolon (ex.: 4!;):" << "\n";
	cout << "> ";

	CalculatorV1::Calculate(tokenStream);

	return 0;
}


