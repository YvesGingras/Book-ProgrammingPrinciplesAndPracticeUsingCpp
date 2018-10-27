/*
 * Created by Yves Gingras on 2018-10-24.
 */

#include <iostream>
#include <vector>
#include "CalculatorV2.h"
 using namespace std;

namespace CalculatorV2
{

	void TokenStream::PutBack(Token token) {
		if (isBufferFull)
			throw runtime_error("Error: 'token' buffer is isBufferFull.");

		buffer = token;
		isBufferFull = true;
	}

	Token TokenStream::Get(std::string modifiedBy) {
		vector<char> operators {'(', ')', '+', '-', '*', '/'};
		vector<char> numbers {'.', '0', '1', '2', '3', '4', '5', '6', '7', '8','9'};
		vector<char> menuItems {';', 'q'};

		if (isBufferFull) {
			isBufferFull = false;
			return buffer;
			}

		char input{};
		cin >> input;

		for (const auto& menuItem : menuItems) {
			if (menuItem == input)
				return menuItem;
		}

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

	double Expression() {
		double left{Term()};
		TokenStream tokenStream;
		Token token{tokenStream.Get("Modified by YG")};

		while (true) {
			switch (token.kind) {
				case '+' :
					left += Term();
					token = tokenStream.Get("Modified by YG");
					break;
				case '-':
					left -= Term();
					token = tokenStream.Get("Modified by YG");
					break;
				default:
					tokenStream.PutBack(token);
					return left; // finally: o more + or -: return the answer
			}
		}

	}

	double Term() {
		double left = Primary();
		TokenStream tokenStream;
		Token token = tokenStream.Get("Modified by YG");     // getToken the next token

		while (true) {
			switch (token.kind) {
				case '*':
					left *= Primary();
					token = tokenStream.Get("Modified by YG");
					break;
				case '/': {
					double primary = Primary();
					if (primary == 0)
						throw runtime_error("Term()\n"
						                    "Error: Divide by zero");
					left /= primary;
					token = tokenStream.Get("Modified by YG");
					break;
				}
				default:
					tokenStream.PutBack(token);
					return left;
			}
		}
	}

	double Primary() {
		return 0;
	}
}