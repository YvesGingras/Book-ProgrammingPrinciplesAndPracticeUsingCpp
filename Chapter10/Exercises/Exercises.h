/*
 * Created by Yves Gingras on 2018-11-29.
 */

#ifndef CHAPTER10_EXERCISES_H
#define CHAPTER10_EXERCISES_H

#include <iostream>
#include <vector>


class Exercise01 {
public:
	static inline std::vector<int> mIntValues;

	static int GetSum(std::istream& inStream);
};

namespace Exe2To4
{
	struct Reading {
		int hour{};

		double temperature{};

		Reading(int hour, double temperature);
	};

	std::vector<Reading> GetSampleReadings();
	void StoreTemps(std::ostream& outStream);

	std::ostream& operator<<(std::ostream& os, const Reading& reading);
}; /*Exe2To4*/

#endif //CHAPTER10_EXERCISES_H
