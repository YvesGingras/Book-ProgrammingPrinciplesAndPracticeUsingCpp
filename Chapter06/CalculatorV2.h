/*
 * Created by Yves Gingras on 2018-10-24.
 */

#ifndef CHAPTER06_CALCULATORV2_H
#define CHAPTER06_CALCULATORV2_H

#include "Declarations.h"

namespace CalculatorV2
{
	class TokenStream {
	public:
		TokenStream() = default;

		Token Get();
		Token Get(std::string modifiedBy);
		void PutBack(Token token);

	private:
		bool isBufferFull{false};
		Token buffer{' '};
	};


	double Expression();
	double Term();
	double Primary();

}



#endif //CHAPTER06_CALCULATORV2_H
