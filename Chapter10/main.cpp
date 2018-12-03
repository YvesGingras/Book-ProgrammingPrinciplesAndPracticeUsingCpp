#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include "FinalExample.h"
#include "Invalid.h"
#include "Drill/Drill.h"
#include "Exercises/Exercises.h"

using namespace std;


//Utility
ifstream GetInFileStream(const string& filePath) {
	ifstream inStringFile{filePath};
	if (!inStringFile)
		throw Invalid("\nGetInFileStream()\n"
		              "Error: Can't open file '" + filePath + "'.");

	inStringFile.exceptions(inStringFile.exceptions() | ios_base::badbit); //implicit exception throw for bad
	return inStringFile;
}

ofstream GetOutFileStream(const string& filePath) {
	ofstream OutStreamFile{filePath};
	if (!OutStreamFile)
		throw Invalid("\nGetOutFileStream()\n"
		              "Error: Can't open file '" + filePath + "'.");

	OutStreamFile.exceptions(OutStreamFile.exceptions() | ios_base::badbit); //implicit exception throw for bad
	return OutStreamFile;
}

void FirstLine(const string& name) {
	cout << "\n*" << name << "*" << endl;
}

void LastLine() {
	cout << "----------------------------------\n";
}

//Final Example
void ReadInTestMode(const string& projectPath) {
	/*testing reading temperatures*/
	string temperaturesFilePath{projectPath + "Temperatures.txt"};
	ifstream inStringTemperatures{GetInFileStream(temperaturesFilePath)};

	vector<Temperatures::Reading> Temperatures{Temperatures::TemperaturesReading(inStringTemperatures)};
	cout << "\nTesting 'temperatures only reading" << endl;
	for (const auto& temperature : Temperatures)
		cout << "Day of the month: " << temperature.day
		     << " - Hour of the day: " << temperature.hour
		     << " - Temperature: " << temperature.temperature << endl;

	/*Testing getting 'month marker'*/
	string monthsFilePath{projectPath + "Months.txt"};
	ifstream inStringMonths{GetInFileStream(monthsFilePath)};

	vector<Temperatures::Month> Months{Temperatures::MonthsReading(inStringMonths)};
	cout << "\nTesting 'Months' only" << endl;
	for (const auto& month : Months) {
		cout << "Month: '" << month.month << "'" << endl;
	}

	/*Testing getting 'year marker'*/
	string yearsFilePath{projectPath + "Years.txt"};
	ifstream inStringYears{GetInFileStream(yearsFilePath)};

	vector<Temperatures::Year> Years{Temperatures::YearsReading(inStringYears)};
	cout << "\nTesting 'years' only" << endl;
	for (const auto& year : Years) {
		cout << "Year: '" << year.year << "'" << endl;
	}
}

void RunFinalExample() {
	FirstLine("RunFinalExample");

	const string projectPath{}; //set in the app config for now.

	if (Temperatures::isTestingMode)
		ReadInTestMode(projectPath);
	else {
		/*Get and print complete  years data*/
		string yearsCompleteFilePath{projectPath + "YearsComplete.txt"};
		ifstream inStringYearsComplete{GetInFileStream(yearsCompleteFilePath)};

		cout << "\nYears complete data." << endl;
		vector<Temperatures::Year> years{Temperatures::YearsReading(inStringYearsComplete)};
		PrintTemperaturesData(years);
	}

	LastLine();
}

//Drill
void RunDrill() {
	/*
	Valid Input sample:
	(2,5) (2.2,5.5) (2.25,7.25) (3.4,5.5) (8.25,103.125) (122,236.625) (0.25,0.125) q

	 Error input sample:
	 (8.25,103.125) (122,error) (0.25,0.125) q
	 (8.25,103.125) (0.25,0.125) (122,error) (0.25,0.125) q
    */

	FirstLine("RunDrill()");
	try {

		cout << "Enter coordinates in the format '(x.x, y.y): \n"
		        "Type 'q' when your done." << endl;

		vector<Drill::Point> points;
		while (true) {
			Drill::Point point{};

			if (!(cin >> point)) {
				Drill::EndOfLoop(cin,Drill::quit,"Console input error.");
				break;

			}
			points.push_back(point);
		}
		Drill::PrintPoints(points);

		//write to file
		const string projectPath{
				"/Users/yvesgingras/Code/Repos/Book-ProgrammingPrinciplesAndPracticeUsingCpp/Chapter10/Drill/"};
		string pointsFileName{projectPath + "MyData.txt"};
		ofstream outFileStream{GetOutFileStream(pointsFileName)};

		for (const auto& currentPoint : points) {
			outFileStream << '(' << currentPoint.x << ',' << currentPoint.y << ')' << endl;
		}
		outFileStream.close();

		//Read from file
		ifstream inFileStream{GetInFileStream(pointsFileName)};
		vector<Drill::Point> processedPoints;
		for (Drill::Point currentPoint; inFileStream >> currentPoint;) {
			processedPoints.push_back(currentPoint);
		}

		Drill::EndOfLoop(inFileStream,Drill::quit,"Error reading from file '" + pointsFileName + "'.");

		//check vectors for equality.
		for (int i = 0; i < points.size(); ++i) {
			if (points[i] != processedPoints[i]) {
				ostringstream point{}; point << points[i];
				ostringstream processedPoint{}; processedPoint << processedPoints[i];

				throw Invalid("Vector of Point(s) comparison.\n"
				              "Error: Points are not equal: " + point.str() + " | " + processedPoint.str());
			}
		}
		Drill::PrintPoints(processedPoints);
	}
	catch (Invalid& e) {
		throw Invalid(e.m_errorMessage);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
		                    "Program is terminating...");
	}

	LastLine();
}

//Exercises
void RunExercise01() {
	FirstLine("RunExercise01");

	const string Exerc1FileName{"/Users/yvesgingras/Code/Repos/Book-ProgrammingPrinciplesAndPracticeUsingCpp/"
							        "Chapter10/Exercises/Exercise01.txt"};

	ifstream inFileStream{GetInFileStream(Exerc1FileName)};

	int sum{Exercise01::GetSum(inFileStream)};
	vector<int> values = Exercise01::mIntValues;

	for (int i = 0; i < values.size(); ++i) {
		if (i == values.size() - 1) {
			cout << to_string(values[i]);
			break;
		}
		cout << to_string(values[i]) << " + ";
	}

	cout << " = " << to_string(sum) << endl;
	LastLine();
}

void RunExercises02To04() {
	using namespace Exe2To4;

	string folderPath{"/Users/yvesgingras/Code/Repos/Book-ProgrammingPrinciplesAndPracticeUsingCpp/Chapter10/Exercises/"};
	string fileName{"RawTemps.txt"};
	ofstream outFileStream{GetOutFileStream(folderPath + fileName)};

	StoreTemps(outFileStream);
}


int main() {
	cout << "Hello, Chapter10!" << endl;

	try {
//		RunFinalExample();
//		RunDrill();
//		RunExercise01();
		RunExercises02To04();
	}
	catch (fstream::ios_base::failure& e) {
		auto exceptionWhat{string(e.what())};
		cerr << (exceptionWhat);
	}

	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		cerr << (exceptionWhat);
	}
	catch (Invalid& invalid) {
		cerr << (invalid.m_errorMessage);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
		                    "Program is terminating...");
	}
	return 0;
}
