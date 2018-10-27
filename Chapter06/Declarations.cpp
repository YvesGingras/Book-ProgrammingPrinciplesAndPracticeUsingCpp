//
// Created by Yves Gingras on 2018-10-23.
//

#include <iostream>
#include <vector>
#include "Declarations.h"

using namespace std;

/**
 * @brief Recoded by me.
 * @return
 */
Token GetToken(std::string modifiedBy) {
	vector<char> operators {'(', ')', '+', '-', '*', '/'};
	vector<char> numbers {'.', '0', '1', '2', '3', '4', '5', '6', '7', '8','9'};

	char input{};
	cin >> input;




	for (const auto& currentOperator : operators) {
		if (currentOperator == input)
			return Token{input};
	}

	for (const auto& item : numbers) {
		if (item == input) {
			cin.putback(input);
			double value;
			cin >> value;
			return Token{'8', value};
		}
	}

	throw runtime_error("GetToken(string modifiedBy)\n"
	                    "Error: Bad token.");
}

/**
 * @brief Taken as in from the book.
 * @param fake
 * @return
 */
Token GetToken() {
	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
		//not yet   case ';':    // for "print"
		//not yet   case 'q':    // for "quit"
		case '(': case ')': case '+': case '-': case '*': case '/':
			return Token(ch);        // let each character represent itself
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			cin.putback(ch);         // put digit back into the input stream
			double val;
			cin >> val;              // read a floating-point number
			return Token('8',val);   // let '8' represent "a number"
		}
		default:
			throw runtime_error("GetToken()\n"
			                    "Error: Bad token.");
	}
}

