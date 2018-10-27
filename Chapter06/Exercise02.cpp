
//
// Created by Yves Gingras on 2018-10-26.
//

/*
 Exercise 2, page 206
 Add the ability to use {} as well as () in the program,
 so that {(4+5)*6} /(3+4) will be a valid expression.
 */

/*
Tested expressions and their expected results.

Expressions                     Result
2+{4+6};
2+(2*(4+6)); or 2+(2*{4+6});    22
*/


#include <iostream>

using namespace std;
//#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

namespace Exercise02
{

	class Token
	{
	public:
		char kind;        // what kind of token
		double value;     // for numbers: a value
		Token(char input)    // make a Token from a char
				: kind(input), value(0) { }

		Token(char input, double value)     // make a Token from a char and a double
				: kind(input), value(value) { }
	};

//------------------------------------------------------------------------------

	class TokenStream
	{
	public:
		TokenStream();   // make a TokenStream that reads from cin
		Token getToken();      // get a Token (getToken() is defined elsewhere)
		void putback(Token token);    // put a Token back
	private:
		bool isBufferFull;        // is there a Token in the buffer?
		Token buffer;     // here is where we keep a Token put back using putback()
	};

//------------------------------------------------------------------------------

// The constructor just sets isBufferFull to indicate that the buffer is empty:
	TokenStream::TokenStream()
			: isBufferFull(false), buffer(0)    // no Token in buffer
	{
	}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the TokenStream's buffer:
	void TokenStream::putback(Token token) {
//	if (isBufferFull) error("putback() into a isBufferFull buffer");
		if (isBufferFull) throw runtime_error("putback() into a isBufferFull buffer");
		buffer = token;       // copy token to buffer
		isBufferFull = true;      // buffer is now isBufferFull
	}

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

	TokenStream tokenStream;        // provides getToken() and putback()

//------------------------------------------------------------------------------

	double Expression();    // declaration so that Primary() can call Expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
	double Primary() {
		Token token = tokenStream.getToken();
		switch (token.kind) {
			case '(':    // handle '(' Expression ')'
			{
				double expression = Expression();
				token = tokenStream.getToken();
				if (token.kind != ')') throw runtime_error("')' expected");
				return expression;
			}
			case '{':    // handle '(' Expression ')'
			{
				double expression = Expression();
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

//------------------------------------------------------------------------------

// deal with *, /, and %
	double Term() {
		double left = Primary();
		Token token = tokenStream.getToken();        // getToken the next token from token stream

		while (true) {
			switch (token.kind) {
				case '*':
					left *= Primary();
					token = tokenStream.getToken();
					break;
				case '/': {
					double d = Primary();
					if (d == 0) throw runtime_error("divide by zero");
					left /= d;
					token = tokenStream.getToken();
					break;
				}
				default:
					tokenStream.putback(token);     // put token back into the token stream
					return left;
			}
		}
	}

//------------------------------------------------------------------------------

// deal with + and -
	double Expression() {
		double left = Term();      // read and evaluate a Term
		Token token = tokenStream.getToken();        // getToken the next token from token stream

		while (true) {
			switch (token.kind) {
				case '+':
					left += Term();    // evaluate Term and add
					token = tokenStream.getToken();
					break;
				case '-':
					left -= Term();    // evaluate Term and subtract
					token = tokenStream.getToken();
					break;
				default:
					tokenStream.putback(token);     // put token back into the token stream
					return left;       // finally: no more + or -: return the answer
			}
		}
	}

//------------------------------------------------------------------------------
} /*namespace Exercise02*/

int main_NotCurrentlyInUse() {
	try {
		double value = 0;

		cout << "Exercise 02\n"
		        "Enter expression: " << '\n';
		while (cin) {
			Exercise02::Token token = Exercise02::tokenStream.getToken();

			if (token.kind == 'q') break; // 'q' for quit
			if (token.kind == ';')        // ';' for "print now"
				cout << "= " << value << '\n';
			else
				Exercise02::tokenStream.putback(token);
			value = Exercise02::Expression();
		}
	}
	catch (exception& e) {
		cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Oops: unknown exception!\n";
		return 2;
	}
}

//------------------------------------------------------------------------------