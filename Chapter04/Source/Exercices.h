//
// Created by Yves Gingras on 2018-10-06.
//

//#ifndef CHAPTER04_EXERCICES_H
#ifndef CHAPTER04_EXERCICES_H
#define CHAPTER04_EXERCICES_H


#include <vector>
#include <algorithm>

///#include "std_lib_facilities.h"
#include "Exercices.h"
#include "Utilities.h"


using namespace std;

void Exercise03();

/*
 Read a sequence of doubles into a vector. Think of each value as the distance between
two cities along a given route. Compute and print the total distance (the sum of all distances).
Find and print the smallest and greatest distance between two neighboring cities.
Find and print the mean distance between two neighboring cities.
 */
void Exercise03() {
	FirstLine("Exercise03()");

	vector<double> distances;
	double sum{};
	double min{};
	double max{};

	string controlValue{"ok"};
	cout<< "Enter distances followed by '|' to end the data entry process : ";
	//sample data: 12 3 25 26.5 32.7 40 45.2 8 7.25

	while (controlValue != "|") {
		double inputValue{};

		if (cin >> inputValue) {
			distances.push_back(inputValue);
		}
		else {
			controlValue = "|";

			for (const auto& distance : distances)
				sum += distance;

			sort(distances.begin(), distances.end());

			cout << "The total distance is: " << sum << '\n'
			     << "The smallest distance is: " << distances[0] << '\n'
			     << "The greatest distance is: " << distances[distances.size() - 1] << '\n'
			     << "The average distance is: " << sum / distances.size()<< '\n';

			cout << "Bye!" << endl;
		}
	}

//		LastLine();
}


#endif //CHAPTER04_EXERCICES_H
