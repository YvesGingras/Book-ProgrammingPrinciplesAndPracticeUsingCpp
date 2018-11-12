/*
 * Created by Yves Gingras on 2018-11-09.
 *
 * The calculator as completed after exercise 3, of chapter 7.
 *
 */

#include "Calculator.h"


#include "Calculator.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

namespace Calculator
{
	vector<Variable> variables{};

	//TokenStream class
	TokenStream::TokenStream(std::istream& inStream)
			: isBufferFull(false), buffer(0),inStream(inStream)    // no Token in buffer
	{
	}

	void TokenStream::putback(Token token) {
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
			buffer.callName = "";
			isBufferFull = false;
			return tempBuffer;
		}

		char input;
		cin >> input;    // note that >> skips whitespace (space, newline, tab, etc.)

		switch (input) {
			case quit:
			case print:
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
			case ',':
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
				if (isalpha(input) || input == '#') { /*Drill.10: use '#' instead of 'let'.*/
					string stringValue;
					stringValue += input;

					while (cin.get(input) && (isalpha(input) || isdigit(input) || input == '_'))
						stringValue += input;

					cin.putback(input);

					//a variable declaration
					if (stringValue == declarationKey)
						return Token(let);  // return a new 'L' Token with no value.

					if (stringValue == constKey)
						return Token{constant};

					if (stringValue == squareRootKey)
						return Token(function, stringValue);  // return a new 'F' Token with no value.

					if (stringValue == powKey)
						return Token(function, stringValue);  // return a new 'F' Token with no value.

					if (stringValue == exitKey){
						return Token(quit); /*Drill.11: use keyword 'exit' to quit.*/
					}

					//return an 'a' Token with the the variable name as value.
					return Token{name,stringValue};
				}

				throw runtime_error("\nGetToken()\n"
				                    "Error: Bad token");
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
	Variable::Variable(const string& name, double value, bool isVariable)
			: name(name), value(value), isVariable(isVariable) {}

	//stand alone methods.
	int Calculate(TokenStream& tokenStream) {
		auto isFirstLoopDone{false};
		PresetVariables();

		while (tokenStream.inStream)
			try
			{
				if (isFirstLoopDone)
					cout << prompt;
				Calculator::Token token = tokenStream.getToken();

				while (token.kind == print)
					token = tokenStream.getToken(); //eat ';'

				if (token.kind == quit) // 'q' for quit
					return 0;

				tokenStream.putback(token);

				cout << result << Calculator::Statement(tokenStream) << endl;
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
			case constant: //kind == 'C'
				return Declaration(tokenStream, token.kind);
			case function: // kind == 'F'
				return FunctionCall(tokenStream, token.callName);
			default:
				tokenStream.putback(token);
				return Expression(tokenStream);
		}
	}

	double Declaration(TokenStream& tokenStream, Token variableToken) {
		Token token = tokenStream.getToken(); // first; the 'a' token (for 'let' input characters...)

		if (token.kind != name)
			throw runtime_error("\nDeclaration()\n"
			                    "Error: 'name' expected.");

		string variableName = token.callName; //... and the 'a' token associated value: the variable name.

		auto token2 = tokenStream.getToken(); //second; the '=' input character, preceding the 'value' input characters.
		if (token2.kind != '=')
			throw runtime_error("\nDeclaration()\n"
			                    "Error: '=' missing in declaration of " + variableName);

		double expression = Expression(tokenStream);
		DefineVariable(variableName, expression,variableToken.kind == let);

		return expression;
	}

	//not quite right yet as it considers the expression up to the ";" as being the argument,
	// such as "sqrt(25) + 2;" being processed as "sqrt(27);"...
	double FunctionCall(TokenStream& tokenStream, string functionName) {
		auto token = tokenStream.getToken();

		if (token.kind != '(')
			throw runtime_error("\nFunctionCall()\n"
			                    "Error: use '()' to enclose the expression pass to the function.");
		tokenStream.putback(token);

		//square root function
		if (functionName == squareRootKey) {
			auto expression = Expression(tokenStream);

			if (expression < 0)
				throw runtime_error("\nFunctionCall()\n"
				                    "Error: Value pass to the function must be positive.");
			return  Sqrt(expression);
		}

		//power function
		/* Far from being done. For now gives the right output when entry syntax is strickly correct.
		 * Ex.: one single entry as 'pow(2.5,3);
		 * Also, no error management, just moving along. */
		if (functionName == powKey) {
			Token openParenthesis = tokenStream.getToken(); // no use of '(', to the next token...
			Token argument1 = tokenStream.getToken(); //
			Token comma = tokenStream.getToken(); // no use
			Token argument2 = tokenStream.getToken();
			Token closingParenthesis = tokenStream.getToken(); // no use of ')'..

			return Pow(argument1.value,int(argument2.value));
		}


		throw runtime_error("\nFunctionCall()\n"
		                    "Error: No function name '" + functionName + "'.");

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
						throw runtime_error("\nTerm()\n"
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
			case name: {
				Token tokenNext = tokenStream.getToken(); /*from book's solution*/
				if (tokenNext.kind == '=') {
					double expression = Expression(tokenStream);
					SetValue(token.callName,expression);
					return expression;
				}
				tokenStream.putback(tokenNext);
				return GetValue(token.callName);
			}
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
	double DefineVariable(string variableName, double variableValue, bool isVariable) {
		if (isVariableDeclared(variableName))
			throw runtime_error("\nDefineVariable\n"
			                    "Error: Variable already declared.");

		variables.emplace_back(Variable(variableName,variableValue,isVariable));

		return variableValue;
	}

	//looks for a given variable name, and returns its value.
	double GetValue(string variableName) {
		for (const auto& variable : variables)
			if (variable.name == variableName)
				return variable.value;

		throw runtime_error("\nGetValue()\n"
		                    "Error: undefined variable '" + variableName + "'.");
	}

	//sets the a new value to a variable already present.
	void SetValue(string variableName, double variableValue) {
		for (auto& variable : variables) {
			if (variable.name == variableName) {
				if (!variable.isVariable)
					throw runtime_error("\nSetValue()\n"
					                    "Error: '" + variableName + "' is a constant.");

				variable.value = variableValue;
				return;
			}
		}
		throw runtime_error("SetValue()\n"
		                    "Error: undefined variable '" + variableName + "'.");
	}

	// Set predefined variables at program launch.
	void PresetVariables() {
		DefineVariable("pi", 3.1415926535, false);
		DefineVariable("e", 2.7182818284, false);
		DefineVariable("k", 1000);
		DefineVariable("x", 2.22);
		DefineVariable("y", 4.44);
		DefineVariable("z", 6.66);
	}

	// Calculates 'n!'
	int GetFactorial(int nValue) {
		if (nValue < 0)
			throw runtime_error("GetFactorial()\n"
			                    "Input must be a positive integer. Received '" + to_string(nValue) + "'.");

		return nValue==0 ? 1 : nValue*GetFactorial(nValue-1);
	}

	// calculates de square root of a given number.
	double Sqrt(double number) {
		return std::sqrt(number);
	}

	double Pow(double number, int multiple) {
		return std::pow(number,multiple);
	}
} /*CalculatorV1*/