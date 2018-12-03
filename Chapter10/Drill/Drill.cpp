/*
 * Created by Yves Gingras on 2018-11-25.
 */

#include <iostream>
#include "Drill.h"
#include "../Invalid.h"

using namespace std;
namespace Drill
{
	//Method used before implementing 'operator>>
	vector<Drill::Point>& GetPoints(vector<Drill::Point>& points) {
		char char1{}, char2{}, char3{};
		char test{};
		double x{}, y{};

		cout << "Enter 'Point' coordinates in the format '(x.x, y.y)':" << endl;
		cin.exceptions(cin.exceptions() | ios_base::badbit);
		while (cin) {
			cin >> test;
			if (test == quit) {
				cout << "Thanks!" << endl;
				break;
			}

			cin.putback(test);
			cin >> char1 >> x >> char2 >> y >> char3;

			if (cin.fail()) {
				cerr << "Last Input failed! The following entered data was valid:\n";

				PrintPoints(points, true);
				cout << endl;
				/*
				cerr << "Last Input failed!\n";
				if (!points.empty()){
					cerr << "Last Input failed! Valid Data entered so far..." << endl;
					PrintPoints(points);
					cin.clear();
					cin.get();
					continue;
					cout << "\nEnter coordinates: " << endl;
				}

				else
				*/
				throw Invalid("GetPoints()\n"
				              "Error: No valid data for x or y.\n");
			} else
				points.push_back(Point{x, y});
		}
		return points;
	}

	void PrintPoints(const vector<Point>& points, bool isFromErrorCall) {
		if (!points.empty()) {
			if (!isFromErrorCall)
				cout << "\nList of entered coordinate(s):\n";
			for (const auto& point : points)
				cout << "(" << point.x << ',' << point.y << ')' << '\n';
		} else
			cout << "No coordinate(s) entered.\n";
	}

	void EndOfLoop(std::istream& inStream, char terminator, const string& errorMessage) {
		if (inStream.fail()) {
			inStream.clear();
			char input{};
			if ((inStream >> input && input == Drill::quit) || inStream.eof())
				return;

			throw Invalid(errorMessage);
		}
	}

	std::istream& operator>>(std::istream& inStream, Point& point) {
		char parenthesisOpen{}, comma{}, parenthesisClose{};
		double x{}, y{};

		if ((inStream >> parenthesisOpen && parenthesisOpen != '(')) {
			inStream.unget();
			inStream.clear(ios_base::failbit);
			return inStream;
		}

		inStream >> x >> comma >> y >> parenthesisClose;
		if (parenthesisOpen != '(' || comma != ',' || parenthesisClose != ')') {
			inStream.clear(ios_base::failbit);
			return inStream;
		}

		point.x = x;
		point.y = y;

		return inStream;
	}

	std::ostream& operator<<(std::ostream& os, const Point& point) {
		// TODO review what to print
		os << "(" << point.x << ',' << point.y << ')';
		return os;
	}

	bool operator==(const Point& lhs, const Point& rhs) {
		return lhs.x == rhs.x &&
		       lhs.y == rhs.y;
	}

	bool operator!=(const Point& lhs, const Point& rhs) {
		return !(rhs == lhs);
	}
}/*Drill*/