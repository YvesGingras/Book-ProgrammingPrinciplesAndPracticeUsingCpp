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

//modified Grammar (managing '!' in Chapter 6)
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

//modified Grammar (managing '-' in Chapter 7)
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
    "-" Primary (Chapter 7 modification)
    "+" Primary (Chapter 7 modification)
	"(" Expression ")"
Number:
	floating-point-literal
*/

////New Grammar to implementing the use of user variables (Chapter 7)
/*
Calculation:
	Statement
	Print
	Quit
	Calculation Statement
Statement:
    Declaration
	Expression
Declaration:
	"let" Name "=" Expression
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

//Chapter 7, testing variable functionality.
/*
 let x = 3.4;
 let y = 2;
 x + y *2;
 */
#include "CalculatorV1.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

namespace CalculatorV1
{
	vector<Variable> variables{};

	//TokenStream class
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
			case quit:    // for "print"
			case print:    // for "quit"
			case '(':
			case ')':
			case '{':
			case '}':
			case '+':
			case '-':
			case '*':
			case '/':
			case '!':
			case '%':
			case '=':
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
				return Token(number, value);   // let '8' represent "a number"
			}
			default:
				if (isalpha(input)) {
					string stringValue;
					stringValue += input;

					while (cin.get(input) && (isalpha(input) || isdigit(input)))
						stringValue += input;

					cin.putback(input);
					if (stringValue == declarationKey)
						return Token(let);  // return a new 'L' Token with no value.

					return Token{name,stringValue};   //return an 'a' Token with the following characters as its name.
				}

				throw runtime_error("Bad token");
		}
	}

	/**
	 * @brief Ignore and suppress all input to given character.
	 */
	void TokenStream::Ignore(char searchedKind) {
		if (isBufferFull && searchedKind == buffer.kind){
			isBufferFull = false;
			return;
		}
		isBufferFull = false;

		char input{0};
		while (cin>>input)
			if (input == searchedKind)
				return;
	}

	//Variable class
	Variable::Variable(const string& name, double value)
		: name(name), value(value) { }

	//stand alone methods.
	int Calculate(TokenStream& tokenStream) {
		auto isFirstLoopDone{false};
		PresetVariables();

		while (cin)
			try
			{


				if (isFirstLoopDone)
					cout << prompt;
				CalculatorV1::Token token = tokenStream.getToken();

				while (token.kind == print)
					token = tokenStream.getToken(); //eat ';'

				if (token.kind == quit) // 'q' for quit
					return 0;

				tokenStream.putback(token);

				cout << result << CalculatorV1::Statement(tokenStream) << endl;
//				tokenStream.getToken(); //Trying(!): just empty the buffer
//				cout << prompt;
				isFirstLoopDone = true;
			}
			catch (exception& e) {
				cerr << e.what() << '\n';
				CleanUpMess(tokenStream);
			}
			catch (...) {
				throw runtime_error("An unknown exception has occurred in 'Calculate()'!\n"
				                    "Program is terminating...");
			}
		return 0;
	}

	double Statement(TokenStream& tokenStream) {
		auto token = tokenStream.getToken();
		switch (token.kind) {
			case let: // kind =='L':
				return Declaration(tokenStream);
			default:
				tokenStream.putback(token);
				return Expression(tokenStream);
		}
	}

	double Declaration(TokenStream& tokenStream) {
		Token token = tokenStream.getToken(); // first; the 'a' token (for 'let' input characters...)

		if (token.kind != name)
			throw runtime_error("Declaration()\n"
			                    "Error: constant 'name' expected.");

		string variableName = token.variableName; //... and the 'a' token associated value: the variable name.

		auto token2 = tokenStream.getToken(); //second; the '=' input character, preceding the 'value' input characters.
		if (token2.kind != '=')
			throw runtime_error("Declaration()\n"
			                    "Error: '=' missing in declaration of " + variableName);

		double expression = Expression(tokenStream);
		DefineVariable(variableName, expression);

		return expression;
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
				case '%': {
					double factorial = Factorial(tokenStream);
					if (factorial == 0)
						throw runtime_error("Term()\n"
						                    "Error: Divided by zer.");

					left = fmod(left,factorial);
					token = tokenStream.getToken();
					break;
				}

				default:
					tokenStream.putback(token);     // put token back into the token stream
					return left;
			}
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
			case number:
				return token.value;  // return the number's value
			case name:
				return GetValue(token.variableName);
			case '-':
				return - Primary(tokenStream);
			case '+':
				return + Primary(tokenStream);
			default:
				throw runtime_error("Primary expected");
		}
	}

	//  cleans messy input causing an error, and continue to the next expression.
	void CleanUpMess(TokenStream& tokenStream) {
		tokenStream.Ignore(print);
	}

	bool isVariableDeclared(const string& searchedVariable) {
		for (const auto& variable : variables)
			if (variable.name == searchedVariable)
				return true;

		return false;
	}

	// Adds a new variable to variables vector, and returns its value.
	double DefineVariable(string variableName, double variableValue) {
		if (isVariableDeclared(variableName))
			throw runtime_error("DefineVariable\n"
					   "Error: Variable already declared.");

		variables.emplace_back(Variable(variableName,variableValue));

		return variableValue;
	}

	//looks for a given variable name, and returns its value.
	double GetValue(string variableName) {
		for (const auto& variable : variables)
			if (variable.name == variableName)
				return variable.value;

		throw runtime_error("GetValue()\n"
					  "Error: undefined variable '" + variableName + "'.");
	}

	//sets the a new value to a variable already present.
	void SetValue(string variableName, double variableValue) {
		for (auto& variable : variables) {
			if (variable.name == variableName)
				variable.value = variableValue;
		}
		throw runtime_error("SetValue()\n"
		                    "Error: undefined variable '" + variableName + "'.");
	}

	// Set predefined variables at program launch.
	void PresetVariables() {
		DefineVariable("pi",3.1415926535);
		DefineVariable("e",2.7182818284);
		DefineVariable("x",2.22);
		DefineVariable("y",4.44);
		DefineVariable("z",6.66);
	}

	// Calculates 'n!'
	int GetFactorial(int nValue) {
		if (nValue < 0)
			throw runtime_error("GetFactorial()\n"
			                    "Input must be a positive integer. Received '" + to_string(nValue) + "'.");

		return nValue==0 ? 1 : nValue*GetFactorial(nValue-1);
	}
} /*CalculatorV1*/