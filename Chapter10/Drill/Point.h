//
// Created by Yves Gingras on 2018-11-26.
//

#ifndef CHAPTER10_POINT_H
#define CHAPTER10_POINT_H

#include <iostream>


namespace Drill
{
	struct Point
	{
		double x{};
		double y{};
	};

	std::istream& operator>>(std::istream& inStream, Point& point);

	std::ostream& operator<<(std::ostream& os, const Point& point);
}/*Drill*/
#endif //CHAPTER10_POINT_H
