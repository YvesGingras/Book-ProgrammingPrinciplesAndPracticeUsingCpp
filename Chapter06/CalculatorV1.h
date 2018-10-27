/*
 * Created by Yves Gingras on 2018-10-23.
 */

#ifndef CHAPTER06_CALCULATORV1_H
#define CHAPTER06_CALCULATORV1_H

#include "Declarations.h"

/*Class 'Token' and method 'GetToken' are defined in 'Declarations' files.*/

namespace CalculatorV1
{

	double Expression();
	double Term();
	double Primary();
}

#endif //CHAPTER06_CALCULATORV1_H
