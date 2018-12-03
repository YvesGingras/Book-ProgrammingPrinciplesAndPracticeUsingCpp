/*
 * Created by Yves Gingras on 2018-11-29.
 */

#include "Exercises.h"
#include "../Invalid.h"

using namespace std;

int Exercise01::GetSum(std::istream& inStream) {
	int sum{};

	for (int value; inStream >> value;) {
		mIntValues.push_back(value);
		sum += value;
	}

	return sum;
}

//Exercises 2 to 4
Exe2To4::Reading::Reading(int hour, double temperature) : hour(hour), temperature(temperature) { }

vector<Exe2To4::Reading> Exe2To4::GetSampleReadings() {
	vector<Reading> readings;

	int hour{0};
	double temperature{6.5};
	for (int i = 0; i < 50; ++i) {
		if (hour > 23)
			hour = 0;

		if (temperature > 14)
			temperature = 6.5;

		readings.emplace_back(hour, temperature);
		hour++;
		temperature += 1.3;
	}

	return readings;
}

void Exe2To4::StoreTemps(ostream& outStream) {
	vector<Exe2To4::Reading> readings = GetSampleReadings();

	for (const auto& reading : readings) {
		outStream << reading << '\n';
	}
}

std::ostream& Exe2To4::operator<<(std::ostream& os, const Exe2To4::Reading& reading) {
	os << reading.hour << ' ' << reading.temperature;

	return os;
}

