/*
 * Created by Yves Gingras on 2018-10-27.
 *
 * The calculator at its completeness state after being through chapter 06,
 * and refactored to work as OPP.
 *
 */

#ifndef CHAPTER07_CALCULATORCH06_H
#define CHAPTER07_CALCULATORCH06_H

namespace CalculatorCh06
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


	double Expression(TokenStream& tokenStream);
	double Primary(TokenStream& tokenStream);
	double Factorial(TokenStream& tokenStream);
	double Term(TokenStream& tokenStream);
	int GetFactorial(int nValue);
}

#endif //CHAPTER07_CALCULATORCH06_H
