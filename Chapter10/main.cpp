#include <iostream>
#include <fstream>
#include "FinalExample.h"
#include "Invalid.h"


using namespace std;

//*******************************************************

/*Utility - Begin*/
ifstream GetInFileStream(const string& filePath) {
	ifstream inStringFile{filePath};
	if (!inStringFile)
		throw Invalid("\nGetInFileStream()\n"
		              "Error: Can't open file '" + filePath + "'.");

	inStringFile.exceptions(inStringFile.exceptions() | ios_base::badbit); //implicit exception throw for bad
	return inStringFile;
}

void FirstLine(const string& name) {
	cout << "\n*" << name << "*" << endl;
}

void LastLine() {
	cout << "----------------------------------\n";
}
/*Utility - End*/


/*Final Example - Begin*/
vector<Temperatures::Reading> TemperaturesReading(ifstream& inStringFile) {
	vector<Temperatures::Reading> readings;

	while (true) {
		Temperatures::Reading reading;
		if (!(inStringFile >> reading)) //set 'isTestingMode=true' to test
			break;
		readings.push_back(reading);
	}
	return readings;
}

vector<Temperatures::Month> MonthsReading(ifstream& inStringFile) {
	vector<Temperatures::Month> months;

	while (true) {
		Temperatures::Month month;
		if (!(inStringFile >> month)) //set 'isTestingMode=true' to test
			break;
		months.push_back(month);
	}
	return months;
}

vector<Temperatures::Year> YearsReading(ifstream& inStringFile) {
	vector<Temperatures::Year> years;

	while (true) {
		Temperatures::Year year;
		if (!(inStringFile >> year)) //set 'isTestingMode=true' to test
			break;
		years.push_back(year);
	}

	return years;
}

void PrintTemperaturesData(const vector<Temperatures::Year>& years) {
	for (const auto& currentYear : years) {
		cout << "\nYear: " << currentYear.year << '\n';

		for (auto currentMonth : currentYear.months) {
			if (currentMonth.month != Temperatures::notAMonth) {
				cout << "  Month: " << Temperatures::monthInputTable[currentMonth.month] << '\n';

				for (int i = 0; i < currentMonth.days.size(); ++i) { //days
					Temperatures::Day currentDay{currentMonth.days[i]};
					bool isDayPrinted{false};

					for (int j = 0; j < currentDay.hours.size(); ++j) { //hours
						if (currentDay.hours[j] != Temperatures::notAReading) {
							if (!isDayPrinted) {
								cout << "    Day of the month: " << to_string(i) << '\n';
								isDayPrinted = true;
							}
							cout << "      Temperature at hour '" << to_string(j) << "': " << to_string(currentDay.hours[j]) << endl;
						}
					}
				}
			}
		}
	}
}


void RunFinalExample() {
//	using namespace Temperatures;
	const string projectPath{};

	FirstLine("RunFinalExample");

	if (Temperatures::isTestingMode) {
		/*testing reading temperatures*/
		string temperaturesFilePath{projectPath + "Temperatures.txt"};
		ifstream inStringTemperatures{GetInFileStream(temperaturesFilePath)};

		vector<Temperatures::Reading> Temperatures{TemperaturesReading(inStringTemperatures)};
		cout << "\nTesting 'temperatures only reading" << endl;
		for (const auto& temperature : Temperatures)
			cout << "Day of the month: " << temperature.day
			     << " - Hour of the day: " << temperature.hour
			     << " - Temperature: " << temperature.temperature << endl;

		/*Testing getting 'month marker'*/
		string monthsFilePath{projectPath + "Months.txt"};
		ifstream inStringMonths{GetInFileStream(monthsFilePath)};

		vector<Temperatures::Month> Months{MonthsReading(inStringMonths)};
		cout << "\nTesting 'Months' only" << endl;
		for (const auto& month : Months) {
			cout << "Month: '" << month.month << "'" << endl;
		}

		/*Testing getting 'year marker'*/
		string yearsFilePath{projectPath + "Years.txt"};
		ifstream inStringYears{GetInFileStream(yearsFilePath)};

		vector<Temperatures::Year> Years{YearsReading(inStringYears)};
		cout << "\nTesting 'years' only" << endl;
		for (const auto& year : Years) {
			cout << "Year: '" << year.year << "'" << endl;
		}
	}

	/*Get and print complete  years data*/
	string yearsCompleteFilePath{projectPath + "YearsComplete.txt"};
	ifstream inStringYearsComplete{GetInFileStream(yearsCompleteFilePath)};

	cout << "\nYears complete data." << endl;
	vector<Temperatures::Year> years{YearsReading(inStringYearsComplete)};
	PrintTemperaturesData(years);

	LastLine();
}

/*Final Example - End*/

int main() {
	cout << "Hello, Chapter10!" << endl;


	try {
		RunFinalExample();

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

vector<Temperatures::Year> GetTemperaturesData(ifstream& inStringFile) {
	vector<Temperatures::Year> years;
	while (true) {
		Temperatures::Year year;
		if (!(inStringFile >> year)) //set 'isTestingMode=true' to test
			break;
		years.push_back(year);
	}

	return years;
}
