//
// Created by Yves Gingras on 2018-10-06.
//


#ifndef CHAPTER00_TRYTHIS_H
#define CHAPTER00_TRYTHIS_H

#include "std_lib_facilities.h"
#include "Utilities.h"

/** @brief Empty Template Method */
void TryThisBlaBla() {
	FirstLine("ExampleBlaBla()");


	LastLine();
}

/** @brief Modify Example3_4 to receive an integer. */
void TryThis3_4() {
	FirstLine("TryThis3_4()");

	FirstLine("Example3_4Float()");

	cout << "please enter a integer value: ";
	int n;
	cin >> n;
	cout << "n == " << n
	     << "\nn+1 == " << n+1
	     << "\nthree times n == " << 3*n
	     << "\ntwice n == " << n+n
	     << "\nn squared == " << n*n
	     << "\nhalf of n == " << n/2
	     << "\nsquare root of n == " << sqrt(n)
	     << endl; // another name for newline ("end of line")

	LastLine();


	LastLine();
}

/** @brief detect repeated words */
void TryThis3_5_1() {
	FirstLine("Example3_5_1()");

	string previous = " ";       // not a word
	string current;

	// need to type 'Ctrl+D' to exit the while loop after the last word has been red.
	while (cin >> current) {       // read a stream of words
		if (previous == current) // check if the word is the same as last
			cout << "repeated word: " << current << '\n';
		previous = current;
	}

	LastLine();
}


#endif //CHAPTER00_TRYTHIS_H
