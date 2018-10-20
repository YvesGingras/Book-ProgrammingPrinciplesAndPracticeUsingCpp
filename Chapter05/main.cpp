#include <iostream>
#include <vector>
#include "Declarations.h"

using namespace std;


int main() {
	cout << "Hello, Chapter 05!\n" << endl;
	try
	{
//		TryThis5_6(4, 3);
//		TryThis5_7();
//		TryThis5_10_1(10,100);
//		Drill();
//		Exercise02();
//		Exercise03();
//		Exercise04();
//		Exercise05();
		Exercise08();

		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << endl;

		return 1;
	}
}

//Definitions
/*Various*/
int Area(int length, int width) {
	if (length<=0 || width<=0)
		throw runtime_error ("Non-positive Area() argument");

	return length*width;
}

int FramedArea(int x, int y) {
	constexpr int frameWidth{2};

	if (x - frameWidth <= 0 || y - frameWidth<=0)
		throw runtime_error("Non-positive Area() argument called by FramedArea()");

	return Area(x-frameWidth,y-frameWidth);
}

void FirstLine(const string& name) {
	cout << "\n*" << name << "*";
}

void LastLine() {
	cout << "----------------------------------\n";
}

/*TryThis's*/
void TryThis5_6(int length, int width) {
	FirstLine("TryThis5_6");

	cout << "Given 'length' = " << length
	     << "\nGiven 'width' = " << width << endl;

	int area1 {Area(length,width)};
	int area2 {FramedArea(length, width)};
	double ratio {double(area1)/area2};



	cout << "\nValue of 'area1' is: " << area1 << endl;
	cout << "\nValue of 'area2' is: " << area2 << endl;
	cout << "\nValue of 'ratio' is: " << ratio << endl;

	LastLine();
}

 /**
  * @brief Find lowest and highest temperature.
  */
void TryThis5_7() {
	vector<double> temps;

	constexpr double minTemperature{-1000};
	constexpr double maxTemperature{1000};

	double highTemperature{minTemperature};
	double lowTemperature{maxTemperature};
	double sum{};


	/* data entry sample
	   76.5 73.5 71.0 73.6 70.1 73.5 77.3 85.3 88.5 91.7 95.9 99.2 98.2 100.6 106.3 112.4 110.2 103.6 94.9 91.7 88.4 85.2 85.4 87.7
	 */
	cout << "\nEnter temperature values separated by a space: (type any character to end data entry)" << endl;
	for (double temp; cin >> temp;)
		temps.push_back(temp);

	for (const auto& temperature : temps) {
		cout << "Temperature: " << temperature << endl;

		if (temperature > highTemperature)
			highTemperature = temperature;

		if (temperature < lowTemperature)
			lowTemperature = temperature;

		sum += temperature;
	 }

	 cout << "\nHighest temperature: " << highTemperature << '\n'
          << "\nLowest temperature: " << lowTemperature << '\n'
          << "\nAverage temperature: " << sum/temps.size();


}

/**
 * @brief  Find a pair of values so that the pre-condition of this version of Area() holds,
 * but the post-condition doesn’t.
 * @pre length and width are positive
 * @post returns a positive value that is the area
 * @remark Cannot find such a pair of value so far. :(
 */
void TryThis5_10_1(int length, int width) {
	if (length<=0 || width<=0)
		throw runtime_error("Area() pre-condition");

	int area {length*width};

	if (area <=0)
		throw runtime_error("Area() post-condition");

	FirstLine("TryThis5_10_1");
	cout << "\nThe area of the rectangle is: " << area << endl;
	LastLine();
}

/*Drill*/
void Drill() {
	try {
		/*1*/
//		Cout << "Success!\n";
		cout << "#1: Success!\n";

		/*2*/
		cout << "#2: Success!\n";

		/*3*/
//		cout << "Success" << !\n"
		cout << "#3: Success!" << "\n";

		/*4*/
//		cout << success << '\n';
		cout << "#4:success" << '\n';

		/*5*/
//		string res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";
		auto res = 7;
		vector<int> v(10);
		v[5] = res;
		cout << "#5: Success!\n";

		/*6*/
//		vector<int> v(10); v(5) = 7; if (v(5)!=7) cout << "Success!\n";
		vector<int> v2(10);
		v2[5] = 5;
		if (v2[5]!=7)
			cout << "#6: Success!\n";

		/*7*/
//		if (cond) cout << "Success!\n"; else cout << "Fail!\n";
		int test{1};
		if (test == 1)
			cout << "7: Success!\n";
		else
			cout << "#7: Fail!\n";

		/*...*/


		/*24*/
//		int x = 4; double d = 5/(x–2); if (d=2*x+0.5) cout << "Success!\n";
		int x = 4;
		double d = 5.0/(x-2);
		if (d==2.5)
			cout << "#24: Success!\n";













	}
	catch (exception& e) {
		string exceptionWhat(e.what());
		throw runtime_error("An error occurred in Drill()" + exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception occurred in Drill()!");
	}
}

/*Exercises*/
double CelsiusToKelvin(double celsius) {
	double kelvin {celsius + 273.15};
	return kelvin;
}

/**
 * @brief Modified for 'Exercise 4'.
 */
double CelsiusToKelvin2(double celsius) {
	if (celsius < -273.15)
		throw runtime_error("Temperature cannot be below 'absolute zero (-273.15deg Celsius).\n"
					  "Program terminated!");

	double kelvin {celsius + 273.15};
	return kelvin;
}

/**
 * @brief Modified for 'Exercise 5'.
 *
 * Add to the program so that it can also convert from Kelvin to Celsius.
 */
double ConvertDegrees(double degrees, char type) {
	constexpr double absolute0Celsius{-273.15};
	constexpr double absolute0kelvin{0};
	constexpr double conversionFactor{273.15};

	if ((type == 'C' && degrees < absolute0Celsius) || (type == 'K' && degrees < absolute0kelvin))
		throw runtime_error("Temperature cannot be below 'absolute zero'.\n"
		                    "Program terminated!");

	double result{};
	result = type == 'K' ? degrees - conversionFactor
						 : degrees + conversionFactor;

	return result;
}


/**
 * @brief The following program takes in a temperature value in Celsius and converts it to Kelvin.
 *
 * This code has many errors in it. Find the errors, list them, and correct the code.
 */
void Exercise02() {
	try {
		double input{};

		cout << "Enter the degrees in celsius: " << endl;
		cin >> input;

		double kelvin {CelsiusToKelvin(input)};
		cout << "The converted Celsius degrees in Kelvin are : " << kelvin << endl;
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error("An exception has occurred in 'Exercise02()': " + exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'Exercise02()'!\n"
		                    "Program is terminating...");
	}
}

void Exercise03() {
	try {
		double input{};

		cout << "Enter the degrees in celsius: " << endl;
		cin >> input;

		if (input < -273.15)
			throw runtime_error("Temperature) cannot be below 'absolute zero (-273.15deg Celsius)."
					   "\nProgram terminating...");

		double kelvin {CelsiusToKelvin(input)};
		cout << "The converted Celsius degrees in Kelvin are : " << kelvin << endl;
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error("An exception has occurred in 'Exercise03()': " + exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'Exercise03()'!\n"
		                    "Program is terminating...");
	}
}

void Exercise04() {
	FirstLine("Exercise04()");

	try {
		double degrees{};

		cout << "\nEnter the degrees in celsius: " << endl;
		cin >> degrees;

		double kelvin {CelsiusToKelvin2(degrees)};
		cout << "The converted Celsius degrees in Kelvin are : " << kelvin << endl;

		LastLine();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'Exercise04()'!\n"
		                    "Program is terminating...");
	}
}

void Exercise05() {
	FirstLine("Exercise05()");

	try {
		double degrees{};
		char type{};

		cout << "\nEnter the degrees type to convert from ('K' for Kelvin, 'C' for Celsius): " << endl;
		cin >>  type;

		//check if input is 'legal'...

		cout << (type == 'K' ? "\nEnter the degrees in kelvin: "
							 : "\nEnter the degrees in celsius: ") << endl;

		cin >> degrees;

		double result {ConvertDegrees(degrees,type)};
		cout << (type == 'K' ? "The converted Kelvin degrees in Celsius are : "
		                     : "The converted Celsius degrees in Kelvin are : ") << result << endl;

		LastLine();
	}
	catch (exception& e) {
		auto exceptionWhat{string(e.what())};
		throw runtime_error(exceptionWhat);
	}
	catch (...) {
		throw runtime_error("An unknown exception has occurred in 'Exercise04()'!\n"
		                    "Program is terminating...");
	}
}

/**
 * @brief
 */
void Exercise08() {
	vector<int> inputValues{};

	//input
	int qtyValues{};
	cout << "Please enter the number of values you want to sum: " << endl;
	cin >> qtyValues;

	int inputValue{};
	cout << "\nPlease enter some integers (enter '|' to stop): " << endl;
	while (cin >> inputValue)
		inputValues.push_back(inputValue);

	//validate input
	if (inputValues.size() < qtyValues)
		throw runtime_error("Exercise08()\n"
					        "Cannot make a sum from " + to_string(qtyValues) +
							     " numbers as " + to_string(inputValues.size()) + " only have been entered.\n"
							"Program terminated!");

	//compute
	int sum{};
	string summedNumbers{};
	for (int i = 0; i < qtyValues; ++i) {
		sum += inputValues[i];
		summedNumbers += " " +  to_string(inputValues[i]);
	}
	summedNumbers += " ";

	//output
	cout << "\nThe sum of the first " << qtyValues << " numbers (" << summedNumbers << ") is " << sum << "." << endl;
}


















