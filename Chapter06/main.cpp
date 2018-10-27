#include <iostream>
#include <vector>
#include "Declarations.h"
#include "CalculatorV1.h"
#include "CalculatorV2.h"

using namespace std;


/**
 * @brief General purpose main()
 *
 * 		Disabled when another 'main()' is used somewhere
 * 		for exercises or other specific purposes such as in:
 *
 * 		Provided6_7.cpp, Exercise02.cpp, Exercise03.cpp
 */
int main_UsingINExercise03()  {
	cout << "Hello, Chapter 06!" << endl;

	try
	{
//		TryThis6_3_4();
//		TryThis6_4_6(); //Calculator version1 (page 194 [Paragraph 6.6])
//		TryYvesVersionTwo6_7();
		Exercise04();

		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << endl;

		return 1;
	}
}


//Definitions
void FirstLine(const string& name) {
	cout << "\n*" << name << "*";
}
void LastLine() {
	cout << "----------------------------------\n";
}

/**
 * @brief First iteration or the calculator implementation (pg175)
 */
void Calculator1() {
	int rvalue{};

	int lvalue{};
	cout << "\nEnter an Expression to evaluate, then add 'x' to process it (e.g., 1+2x).\n"
		    "Expression: ";
	cin >> lvalue;

	if (!cin) throw runtime_error("Error in'Calculator1()': No first operand!"); //input validation

	for (char mathOperator; cin >> mathOperator;) {
		if (mathOperator!='x') cin>>rvalue;
		if (!cin) throw runtime_error("Error in'Calculator1()': No second operand!"); //input validation

		switch (mathOperator) {
			case '+':
				lvalue += rvalue;
				break;
			case'-':
				lvalue -= rvalue;
				break;
			case '*':
				lvalue *= rvalue;
				break;
			case '/':
				lvalue /= rvalue;
				break;
			default:
				cout << "\nResult: " << lvalue << endl;
//				return;
		}
	}
	throw runtime_error("Error in'Calculator1()': Bad Expression!");
}

/**
 * @brief Second iteration or the calculator implementation (pg178)
 */
void Calculator2() {
	vector<Token> tokens;
	bool isFirstLvalueSet{true};

	cout << "\nType an Expression (e.g., 1+2) and hit enter.\n"
	        "Expression: ";

	while (cin.peek() != '\n') {
		auto token = GetToken(std::string());
		tokens.push_back(token);
	}

	if (tokens.size()<3)
		throw runtime_error("Calculator2()\n"
					        "No valid Expression: Requires at least 2 operands and one operator (ex.: '1+2')");

	double result{tokens[0].value}; // the Expression first value (lvalue)
	for (int i = 1; i < tokens.size(); i +=2) {
		if (tokens[i].kind == '+')
			result += tokens[i+1].value;
		else if (tokens[i].kind == '-')
			result -= tokens[i+1].value;
		else if (tokens[i].kind == '*')
			result *= tokens[i+1].value;
		else if (tokens[i].kind == '/')
			result /= tokens[i+1].value;
	}

	cout << "\nResult: " << result << endl;
}

/**
 * @brief Trying implementing the calculator from the examples so far...
 *
 * One is with a switch/case construct and another one with my version or 'GetToken'.
 */
void TryThis6_3_4() {
//	Calculator1(); // page 175 1st implementation,  using switch construct.
	Calculator2(); // page 178 2nd implementation, using GetToken().
}

/**
 * @brief Tying the first version of the calculator with the use of the 'Grammar'...
 *
 * Most of the called code is in 'CalculatorV1' files.
 */
void TryThis6_4_6() {
	try {
		while (cin)
			cout  << CalculatorV1::Expression() << '\n';
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'TryThis6_4_6'!\n"
		                    "Program is terminating...");
	}


}

/**
 * @brief Trying calculator version 2; YG's version.
 *
 * Most of the code in 'CalculatorV2' Files.
 */
void TryYvesVersionTwo6_7() {
	try {
		double value {};
		CalculatorV2::TokenStream tokenStream{};

		while(cin) {
			Token token {tokenStream.Get("Modified by YG")};

			if (token.kind == 'q')
				break;
			if (token.kind == ';')
				cout << "=" << value << '\n';
			else
				tokenStream.PutBack(token);

			value = CalculatorV2::Expression();
		}
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'TryYvesVersionTwo6_7()'!\n"
		                    "Program is terminating...");
	}
}

void Exercise04() {
	vector<NameValue> namesAndValues;
	NameValue nameValue{};
	char test{};

	cout << "Enter a name, followed by its  related value (terminate with 'q'): " << endl;

	while (cin) {
		cin >> test;
		if (test == 'q') {
			break;
		}

		cin.putback(test);
		cin >> nameValue.name >> nameValue.value;
		namesAndValues.push_back(nameValue);
	}

	for (const auto& nameAndValue : namesAndValues)
		cout << "Name: " << nameAndValue.name << ", Value: " << nameAndValue.value << endl;

	cout << "\nThanks you" << endl;
}

