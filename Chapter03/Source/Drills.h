//
// Created by Yves Gingras on 2018-10-06.
//

#ifndef CHAPTER00_DRILLS_H
#define CHAPTER00_DRILLS_H

#include "std_lib_facilities.h"
#include "Utilities.h"

/** @brief This drill is to write a program that produces a simple form letter based on user input.*/
void Drill1Chapter03Pg95() {
	FirstLine("Drill1Chapter03Pg95()");


	cout << "Enter the name of the person you want to write to:\n";
	string firstName;
	cin >> firstName;

	cout << "\nDear " << firstName << ",\n" << endl;
	cout << "     BlaBlaBlaBla\n"
			<< "BlaBlaBlaBla...\n"
			<< "BlaBlaBlaBla...\n"
			<< "BlaBlaBlaBla...\n"
			<< "BlaBlaBlaBla...\n"
			<< "BlaBlaBlaBla...\n"
			<< "BlaBlaBlaBla...\n" << endl;

	string friendName;
	cout << "Enter the name of a friend" << endl;
	cin >> friendName;
	cout << "\nHave you seen " << friendName << " lately?" << endl;

	char friendSex{0};
	cout << "Define the sex of your friend by entering 'm' or 'f' if its 'male' or 'female' respectively:" << endl;
	cin >> friendSex;

	if (friendSex == 'm')
		cout << "\nIf you see " << friendName << ", please ask him to call me." << endl;
	else
		cout << "\nIf you see " << friendName << ", please ask her to call me." << endl;

	int age{0};
	cout << "\nHow old are you " << firstName << " ?" << endl;
	cin >> age;

	cout << "\nI hear you just had a birthday and you are " << age << " years old." << endl;


	if (age <= 0 || age >= 110)
		simple_error("you're kidding");

	/*
	 * etc, etc, etc
	 */



	LastLine();
}



#endif //CHAPTER00_DRILLS_H
