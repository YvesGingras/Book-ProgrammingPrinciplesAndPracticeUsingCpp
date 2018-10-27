/*
 * Created by Yves Gingras on 2018-10-23.
 */

/*Class 'Token' and method 'GetToken' are defined in 'Declarations' files.*/

#include "CalculatorV1.h"

using namespace std;

namespace CalculatorV1
{
	double Expression() {
		double left{Term()};
		auto token{GetToken()};

		while (true) {
			switch (token.kind) {
				case '+' :
					left += Term();
					token = GetToken();
					break;
				case '-':
					left -= Term();
					token = GetToken();
					break;
				default:
					return left; // finally: no more + or -: return the answer
			}
		}

	}

	double Term() {
		double left = Primary();
		auto token = GetToken();     // getToken the next token

		while (true) {
			switch (token.kind) {
				case '*':
					left *= Primary();
					token = GetToken();
					break;
				case '/': {
					double primary = Primary();
					if (primary == 0)
						throw runtime_error("Term()\n"
						                    "Error: Divide by zero");
					left /= primary;
					token = GetToken();
					break;
				}
				default:
					return left;
			}
		}
	}

	double Primary() {
		auto token = GetToken();
		switch (token.kind) {
			case '(':    // handle '(' Expression ')'
			{
				double expression = Expression();
				token = GetToken();
				if (token.kind != ')')
					throw runtime_error("Primary()\n"
					                    "Error: ')' expected");
				return expression;
			}
			case '8':            // we use '8' to represent a number
				return token.value;  // return the number's value
			default:
				throw runtime_error("Primary()\n"
				                    "Error: Primary expected");
		}
	}
}