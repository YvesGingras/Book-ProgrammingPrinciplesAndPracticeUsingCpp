//
// Created by Yves Gingras on 2018-10-20.
//

#ifndef CHAPTER06_DECLARATIONS_H
#define CHAPTER06_DECLARATIONS_H

#include <string>

class Token {
public:
	char kind;
	double value{};

	Token(char kind) : kind(kind) { }
	Token(char kind, double value) : kind(kind), value(value) { }
};

// Used in exercise 04
class NameValue
{
public:
	std::string name;
	double value;
};

void FirstLine(const std::string&);
void LastLine();
Token GetToken(std::string modifiedBy); //yg
Token GetToken(); //from the book
void Calculator1();
void Calculator2();
void TryThis6_3_4();
void TryThis6_4_6();
void TryYvesVersionTwo6_7();
void Exercise04();


#endif //CHAPTER06_DECLARATIONS_H
