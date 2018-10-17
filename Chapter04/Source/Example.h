//
// Created by Yves Gingras on 2018-10-07.
//

#ifndef CHAPTER03_EXAMPLE_H
#define CHAPTER03_EXAMPLE_H

#include "std_lib_facilities.h"
#include "Utilities.h"

/** @brief Compute mean and median temperature*/
void Example4_6_3() {
	FirstLine("Example4_6_3()");

	vector<double> temps;
	for (double temp;cin >> temp;) /*input possible until the type of the data entered is not 'double' (in this case).*/
		temps.push_back(temp);

	//Compute mean temperature
	auto sum {0.0};
	for(auto x : temps)
		sum += x;

	cout << "Average temperature: " << sum/temps.size() << '\n';

	//compute median temperature
	sort(temps);
	cout << "Median temperature: " << temps[temps.size()/2] << '\n';

	LastLine();
}

/** @brief simple dictionary: list of sorted words*/
void Example4_6_4() {
	FirstLine("Example4_6_4()");

	vector<string> words;
	string temp;

	// no way to end the entry process (tried ctrl+D as suggested but it ends the program)
	/*
	 * while (cin>>temp)                // read whitespace separated words
		words.push_back(temp);       // put into vector
	 */

	do {
		cin>>temp;
		if (temp != "Q")
			words.push_back(temp);

		words.push_back(temp);

	} while (temp != "Q");


	cout << "Number of words: " << words.size() << endl;

	sort(words.begin(),words.end()); // sort "from beginning to end"

	for (int i = 0; i< words.size(); ++i)
		if (i==0 || words[i-1]!=words[i]) // is this a new word?
			cout << words[i] << "\n";


	LastLine();
}




#endif //CHAPTER03_EXAMPLE_H
