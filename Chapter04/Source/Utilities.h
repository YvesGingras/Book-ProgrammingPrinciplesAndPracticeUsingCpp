//
// Created by Yves Gingras on 2018-10-07.
//


#ifndef CHAPTER04_UTILITIES_H
#define CHAPTER04_UTILITIES_H

#include<string>
#include <iostream>

using namespace std;

void FirstLine(const string&);
void LastLine();

// Template method
/*
void ExampleBlaBla() {
	FirstLine("ExampleBlaBla()");


	LastLine();
}
*/

void FirstLine(const string& name) {
	cout << "*" << name << "*\n";
}

void LastLine() {
	cout << "----------------------------------\n";
}


#endif //CHAPTER04_UTILITIES_H