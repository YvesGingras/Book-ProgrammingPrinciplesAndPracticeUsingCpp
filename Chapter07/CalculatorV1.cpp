//File description.
/*
 * Created by Yves Gingras on 2018-10-27.
 *
 * First version (as final implemented from chapter 06),
 * and refactored to work as OPP.
 *
 */

//original Grammar
/*
Expression:
    Term
    Expression "+" Term
	Expression "–" Term
Term:
	Primary
	Term "*" Primary
    Term "/" Primary
    Term "%" Primary
Primary:
    Number
	"(" Expression ")"
Number:
	floating-point-literal
*/

//modified Grammar (managing '!')
/*
Expression:
    Term
    Expression "+" Term
	Expression "–" Term
Term:
	Factorial
	Term "*" Factorial
    Term "/" Factorial
    Term "%" Factorial
Factorial:
    Primary
    Primary "!"
Primary:
    Number
	"(" Expression ")"
Number:
	floating-point-literal
*/

//Tested expressions and their expected results.
/*
Expressions                     Result
4!;                             24
(2+5)*4!;                       168
(2+5)*4!+8!;                    40488
((2*3)+2)!;                     40320

Exercise10
    Permutation
    P = 4!/(4-2)!;              12
    P = 8!/(8-6)!;              20160

    Combination
    C = (8!/(8-6)!)/6!;         28

*/


// Chapter 7, Testing different input values and trying to program errors.
/*
1+2+3+4+5+6+7+8 1–2–3–4
!+2
;;;
(1+3;
(1+);
1*2/3%4+5– 6;
();
1+;
+1
1++;
1/0
1/0;
1++2;
–2;
– 2;;;; 1234567890123456; 'a';
q
1+q
1+2; q
 */

#include "CalculatorV1.h"
#include <iostream>

using namespace std;

namespace CalculatorV1
{
	TokenStream::TokenStream()
			: isBufferFull(false), buffer(0)    // no Token in buffer
	{
	}

	void TokenStream::putback(Token token) {
//	if (isBufferFull) error("putback() into a isBufferFull buffer");
		if (isBufferFull) throw runtime_error("putback() into a isBufferFull buffer");
		buffer = token;       // copy token to buffer
		isBufferFull = true;      // buffer is now isBufferFull
	}

	Token TokenStream::getToken() {
		if (isBufferFull) {       // do we already have a Token ready?
			auto tempBuffer = buffer;

			// remove token from buffer
			buffer.kind = '0';
			buffer.value = 0;
			isBufferFull = false;
			return tempBuffer;
		}

		char input;
		cin >> input;    // note that >> skips whitespace (space, newline, tab, etc.)

		switch (input) {
			case ';':    // for "print"
			case 'q':    // for "quit"
			case '(':
			case ')':
			case '{':
			case '}':
			case '+':
			case '-':
			case '*':
			case '/':
			case '!':
				return Token(input);        // let each character represent itself
			case '.':
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': {
				cin.putback(input);         // put digit back into the input stream
				double value;
				cin >> value;              // read a floating-point number
				return Token('8', value);   // let '8' represent "a number"
			}
			default:
				throw runtime_error("Bad token");
		}
	}

	// deal with numbers and parentheses
	double Primary(TokenStream& tokenStream) {
		Token token = tokenStream.getToken();
		switch (token.kind) {
			case '(':    // handle '(' Expression ')'
			{
				double expression = Expression(tokenStream);
				token = tokenStream.getToken();
				if (token.kind != ')') throw runtime_error("')' expected");
				return expression;
			}
			case '{':    // handle '(' Expression ')'
			{
				double expression = Expression(tokenStream);
				token = tokenStream.getToken();
				if (token.kind != '}') throw runtime_error("'}' expected");
				return expression;
			}
			case '8':            // we use '8' to represent a number
				return token.value;  // return the number's value
			default:
				throw runtime_error("Primary expected");
		}
	}

	//deals with '!'
	double Factorial(TokenStream& tokenStream) {
		double left = Primary(tokenStream);
		int intLeft{};
		Token token = tokenStream.getToken();

		while (true) {
			switch (token.kind) {
				case '!': {
					intLeft = GetFactorial(static_cast<int>(left)); // temp variable, casting to integer
					left = intLeft; // implicit conversion back to 'double'
					token = tokenStream.getToken();
					break;
				}
				default:
					tokenStream.putback(token);
					return left;
			}
		}
	}

	// deal with *, /, and %
	double Term(TokenStream& tokenStream) {
		double left = Factorial(tokenStream);
		Token token = tokenStream.getToken();        // getToken the next token from token stream

		while (true) {
			switch (token.kind) {
				case '*':
					left *= Factorial(tokenStream);
					token = tokenStream.getToken();
					break;
				case '/': {
					double factorial = Factorial(tokenStream);
					if (factorial == 0) throw runtime_error("divide by zero");
					left /= factorial;
					token = tokenStream.getToken();
					break;
				}
				default:
					tokenStream.putback(token);     // put token back into the token stream
					return left;
			}
		}
	}

	// deal with + and -
	double Expression(TokenStream& tokenStream) {
		double left = Term(tokenStream);      // read and evaluate a Term
		Token token = tokenStream.getToken();        // getToken the next token from token stream

		while (true) {
			switch (token.kind) {
				case '+':
					left += Term(tokenStream);    // evaluate Term and add
					token = tokenStream.getToken();
					break;
				case '-':
					left -= Term(tokenStream);    // evaluate Term and subtract
					token = tokenStream.getToken();
					break;
				default:
					tokenStream.putback(token);     // put token back into the token stream
					return left;       // finally: no more + or -: return the answer
			}
		}
	}

	// Calculates 'n!'
	int GetFactorial(int nValue) {
		if (nValue < 0)
			throw runtime_error("GetFactorial()\n"
			                    "Input must be a positive integer. Received '" + to_string(nValue) + "'.");

		return nValue==0 ? 1 : nValue*GetFactorial(nValue-1);
	}

} /*CalculatorV1*/