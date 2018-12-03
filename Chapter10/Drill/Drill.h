/*
 * Created by Yves Gingras on 2018-11-25.
 */


#ifndef CHAPTER10_DRILL_H
#define CHAPTER10_DRILL_H

//#include <istream>
#include<vector>
#include "Point.h"

namespace Drill
{
	constexpr char quit {'q'};

	std::vector<Drill::Point>& GetPoints(std::vector<Drill::Point>& points);

	void PrintPoints(const std::vector<Drill::Point>& points, bool isFromErrorCall = false);

	void EndOfLoop(std::istream& inStream, char terminator, const std::string& errorMessage);
}/*Drill*/

#endif //CHAPTER10_DRILL_H
