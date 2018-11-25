#include <utility>

/*
 * Created by Yves Gingras on 2018-11-23.
 */

#ifndef CHAPTER10_INVALID_H
#define CHAPTER10_INVALID_H

#include <string>


class Invalid {

public:
	std::string m_errorMessage{};
	Invalid(std::string errorMessage) : m_errorMessage (std::move(errorMessage)) {}
};



#endif //CHAPTER10_INVALID_H
