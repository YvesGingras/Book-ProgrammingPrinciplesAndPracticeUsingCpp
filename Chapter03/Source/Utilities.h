//
// Created by Yves Gingras on 2018-10-07.
//

#include<string>
#include <iostream>

using namespace std;

#ifndef CHAPTER03_UTILITIES_H
#define CHAPTER03_UTILITIES_H


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


#endif //CHAPTER03_UTILITIES_H
