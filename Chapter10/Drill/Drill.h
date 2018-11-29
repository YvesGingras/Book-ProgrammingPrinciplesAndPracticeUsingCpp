/*
 * Created by Yves Gingras on 2018-11-25.
 */


#ifndef CHAPTER10_DRILL_H
#define CHAPTER10_DRILL_H

#include<vector>
#include "Point.h"

namespace Drill
{
	constexpr char quit {'|'};

	std::vector<Point> GetPoints(std::istream& inStream);

	std::vector<Drill::Point>& GetPoints(std::vector<Drill::Point>& points);

	void PrintPoints(const std::vector<Drill::Point>& points, bool isErrorCall = false);
}/*Drill*/

#endif //CHAPTER10_DRILL_H
