#include <iostream>
#include <cmath>
#include "CalculatorCh06.h"
#include "CalculatorV1.h"
#include "Drill.h"
#include "Exercises.h"
#include "VariousDeclarations.h"

using namespace std;

int main() {
	cout << "Hello, Chapter07!\n" << endl;



	try
	{

/*
		cout << std::boolalpha
		 << isalpha('_')
		 << isdigit('_')
		 << isprint('_')
		 << true;
*/

//		VariousTesting();
//		CalculatorFinalCh06();
//		CalculatorVersion1();
//		DrillCh07();
		ExercisesCh07();

		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << endl;

		return 1;
	}
}

//Definitions
void FirstLine(const string& name) {
	cout << "\n*" << name << "*" << endl;
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


	CalculatorV1::TokenStream tokenStream;

	cout << "CalculatorVersion1\n"
	        "Enter an expression followed by a semicolon (ex.: 4!;):" << "\n";
	cout << CalculatorV1::prompt;

	CalculatorV1::Calculate(tokenStream);

	return 0;
}

//Modification to CalculatorV1 as described in the chapter's Drill (pg 231)
int DrillCh07() {


	Drill::TokenStream tokenStream;

	cout << "Drill\n"
	        "Enter an expression followed by a semicolon (ex.: 4!;):" << "\n";
	cout << Drill::prompt;

	Drill::Calculate(tokenStream);



	return 0;
}

void ExercisesCh07() {
	Exercises::TokenStream tokenStream;
	cout << "Exercises\n"
	        "Enter an expression followed by a semicolon (ex.: 4!;):" << "\n";
	cout << Exercises::prompt;

	Exercises::Calculate(tokenStream);

}

void VariousTesting() {
	FirstLine("Various Testing()");

	cout << "\nTesting (debugging) Function's Token creation'\n" << endl;
	Drill::TokenStream tokenStream;

	cout << "Drill\n"
	        "Enter an expression followed by a semicolon (ex.: 4!;):" << "\n";
	cout << CalculatorV1::prompt;

	Drill::Calculate(tokenStream);

/*
	cout << "Pow() result: " << Drill::Pow(2.5,6) << endl;
	cout << "pow() result: " <<  std::pow(2.5,6) << endl;
	cout << "" << endl;
*/

/*
	cout << "\nTesting 'Drill::Sqrt():'\n"
		 << "Sqrt(2 + 4.3) = "  << Drill::Sqrt(2 + 4.3) << '\n'
		 << "2 + Sqrt(2 + 4.3) = "  << 2 + Drill::Sqrt(2 + 4.3) << '\n'
		 << "((8 + 2) + Sqrt(81)) * 2 = "  << ((8 + 2) +  Drill::Sqrt(81)) * 2 << endl;
*/
	LastLine();
}

