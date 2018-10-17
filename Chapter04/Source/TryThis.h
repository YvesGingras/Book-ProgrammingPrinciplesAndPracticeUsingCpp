//
// Created by Yves Gingras on 2018-10-06.
//

#ifndef CHAPTER04_TRYTHIS_H
#define CHAPTER04_TRYTHIS_H

//#include "std_lib_facilities.h"
#include <vector>
#include "Utilities.h"

double Square(int number);
void TryThis4_4_2_1();
void TryThis4_4_2_3();
void TryThis4_5_1(int, int);
void TryThis4_6_4();

/** @brief Implement square() without using the multiplication operator (4_5_1).
 * Retur
 * */


/**
 * @brief Implement square() without using the multiplication operator (4_5_1).
 * @return a double containing the squa
 */
double Square(int number) {
	int result{};

	for (auto i = number; i > 0 ; --i){
		result  += number;
	}

	return result;
}

/** @brief Writes out a table of characters with their corresponding integer values*/
void TryThis4_4_2_1() {
	FirstLine("TryThis4_4_2_1()");

	auto charInteger {97};
	while (charInteger < 123) {
		char charToPrint = char(charInteger);
		cout << charToPrint << ", ";

		++charInteger;}
	cout << '\n';
	LastLine();
}

/** @brief Writes out a table of characters with their corresponding integer values, using a 'for' loop.*/
void TryThis4_4_2_3() {
	FirstLine("TryThis4_4_2_3()");

	for (int i = 65; i < 123; ++i) {
		if (i < 90 || (i > 96)){
			auto charToPrint = char(i);
			cout << charToPrint << ", ";
		}
	}
	cout << '\n';

	LastLine();
}

/** @brief Run some version of “the first program” using square().*/
void TryThis4_5_1(int lowRangeValue, int highRangeValue) {
	FirstLine("TryThis4_5_1()");

	for (int i = lowRangeValue; i < highRangeValue + 1; ++i) {
		cout << i << " : "  <<  Square(i) << '\n';
	}
	

	LastLine();
}

/** @brief Write a program that “bleeps” out words that you don’t like*/
void TryThis4_6_4() {
	FirstLine("TryThis4_6_4()");

	vector<string> dislikedWords{"Brocoli", "Carrot"};
	vector<string> words;
	string temp;

	//data entry
	do {
		cin>>temp;
		if (temp != "Q")
			words.push_back(temp);
	} while (temp != "Q");

	//compute and output
	for(string& word : words) {
		for(const string& dislikedWord : dislikedWords) {
			if (word == dislikedWord){
				word = "BLEEP";
				break;
			}
		}
		cout << word << '\n';
	}


	LastLine();
}



#endif //CHAPTER04_TRYTHIS_H
