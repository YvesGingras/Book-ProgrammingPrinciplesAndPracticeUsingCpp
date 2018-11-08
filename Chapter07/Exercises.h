/*
 * Created by Yves Gingras on 2018-11-02.
 *
 * This file has been created by a copy of the completed Drill.h one.
 *
 */

#ifndef CHAPTER07_EXERCISES_H
#define CHAPTER07_EXERCISES_H

#include <string>

using std::string;

namespace Exercises
{
	const char number{'8'};
	const char quit{'q'};
	const char print{';'};
	const string prompt{"> "};
	const string result{"= "};
	const char name{'a'};
	const char let{'L'};
	const char constant{'C'};
	const char function{'F'};
	const string powKey{"pow"};
	const string squareRootKey{"sqrt"};
	const string declarationKey {'#'};
	const string exitKey {"exit"};
	const string constKey {"const"};

	class Token
	{
	public:
		char kind{};        // what kind of token
		double value{};     // for numbers: a value
		string callName{};

		Token(char tokenSymbol)    // make a Token from a char
				: kind(tokenSymbol), value(0) { }

		Token(char tokenSymbol, double value)     // make a Token from a char and a double
				: kind(tokenSymbol), value(value) { }

		Token(char tokenSymbol,string name) // make a Token from a char and a string
				: kind(tokenSymbol), callName(name) {}
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
		Variable(const string& name, double value, bool isVariable = true);

		string name{};
		double value{};
		bool isVariable{};
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
	double Declaration(TokenStream& tokenStream, Token variableToken);
	bool isVariableDeclared(const string& searchedVariable);
	double DefineVariable(string variableName, double variableValue, bool isVariable = true);
	void PresetVariables();
	double FunctionCall(TokenStream& tokenStream, string functionName);

	int GetFactorial(int nValue);
	double Sqrt(double number);
	double Pow(double number, int multiple);
} /*CalculatorV1*/




#endif //CHAPTER07_EXERCISES_H
