#include <utility>

/*
 * Created by Yves Gingras on 2018-10-27.
 */

#ifndef CHAPTER07_CALCULATORV1CH07_H
#define CHAPTER07_CALCULATORV1CH07_H

#include <stringlist.h>
#include <string>

using std::string;

namespace CalculatorV1
{
	const char number{'8'};
	const char quit{'q'};
	const char print{';'};
	const string prompt{"> "};
	const string result{"= "};
	const char name{'a'};
	const char let{'L'};
	const string declarationKey{"let"};

	class Token
	{
	public:
		char kind;        // what kind of token
		double value;     // for numbers: a value
		string variableName;

		Token(char tokenSymbol)    // make a Token from a char
				: kind(tokenSymbol), value(0) { }

		Token(char tokenSymbol, double value)     // make a Token from a char and a double
				: kind(tokenSymbol), value(value) { }

		Token(char tokenSymbol,string name) // make a Token from a char and a string
				: kind(tokenSymbol), variableName(name) {}
	};

	class TokenStream
	{
	public:
		TokenStream();   // make a TokenStream that reads from cin
		Token getToken();      // get a Token (getToken() is defined elsewhere)
		void Ignore(char searchedKind);
		void putback(Token token);    // put a Token back
	private:
		bool isBufferFull;        // is there a Token in the buffer?
		Token buffer;     // here is where we keep a Token put back using putback()
	};

	class Variable {
	public:
		Variable(const string& name, double value);

		string name{};
		double value{};
	};

	double Expression(TokenStream& tokenStream);
	double Primary(TokenStream& tokenStream);
	double Factorial(TokenStream& tokenStream);
	double Term(TokenStream& tokenStream);
	int Calculate(TokenStream& tokenStream);
	void CleanUpMess(TokenStream& tokenStream);

	double Statement(TokenStream& tokenStream);
	double GetValue(string variableName);
	void SetValue(string variableName, double variableValue);
	double Declaration(TokenStream& tokenStream);
	bool isVariableDeclared(const string& searchedVariable);
	double DefineVariable(string variableName, double variableValue);
	void PresetVariables();

	int GetFactorial(int nValue);

} /*CalculatorV1*/

#endif //CHAPTER07_CALCULATORV1CH07_H
