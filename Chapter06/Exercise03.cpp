 
/*
 * Created by Yves Gingras on 2018-10-26.
 */

//Exercise description
/*
 Exercise 3, page 206
 Add a factorial operator: use a suffix ! operator to represent “factorial.”

 For example, the expression 7! means 7 * 6 * 5 * 4 * 3 * 2 * 1.
 Make ! bind tighter than * and /; that is, 7*8! means 7*(8!) rather than (7*8)!.
 Begin by modifying the grammar to account for a higher-level operator.
 To agree with the standard mathematical definition of factorial, let 0! evaluate to 1.
 Hint: The calculator functions deal with doubles, but factorial is defined only for ints,
 so just for x!, assign the x to an int and calculate the factorial of that int.
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

#include <iostream>

using namespace std;
//#include "std_lib_facilities.h"

//------------------------------------------------------------------------------

namespace Exercise03
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

	TokenStream tokenStream;        // provides getToken() and putback()

	int GetFactorial(int nValue);
	double Expression();    // declaration so that Primary() can call Expression()

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

	//deals with '!'
	double Factorial() {
		double left = Primary();
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
	double Term() {
		double left = Factorial();
		Token token = tokenStream.getToken();        // getToken the next token from token stream

		while (true) {
			switch (token.kind) {
				case '*':
					left *= Factorial();
					token = tokenStream.getToken();
					break;
				case '/': {
					double factorial = Factorial();
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

	// Calculates 'n!'
	int GetFactorial(int nValue) {
		if (nValue < 0)
			throw runtime_error("GetFactorial()\n"
						        "Input must be a positive integer. Received '" + to_string(nValue) + "'.");

		return nValue==0 ? 1 : nValue*GetFactorial(nValue-1);
	}

/*
	int GetFactorial(int nValue) {
		int result{1};

		for (int i = 1; i < nValue+1; ++i) {
			result = result*i;
		}
		return result;
	}
 */
} /*namespace Exercise03*/

int main() {
	try {
		//Testing 'GetFactorial()'
		/*
		int nValue{};
		cout << "Enter the 'n' value: " << '\n';
		cin >> nValue;
		cout << nValue << "! = " << Exercise03::GetFactorial(nValue);
		cout<<' ';
		*/
		double value = 0;

		cout << "Exercise 03\n"
		        "Enter expression (ex.: 4!;): " << '\n';
		while (cin) {
			Exercise03::Token token = Exercise03::tokenStream.getToken();

			if (token.kind == 'q') break; // 'q' for quit
			if (token.kind == ';')        // ';' for "print now"
				cout << "= " << value << '\n';
			else
				Exercise03::tokenStream.putback(token);
			value = Exercise03::Expression();
		}
		return 0;
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

















