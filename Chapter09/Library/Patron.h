/*
 * Created by Yves Gingras on 2018-11-20.
 *
 * The 'Patron' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#ifndef CHAPTER09_PATRON_H
#define CHAPTER09_PATRON_H

#include <ostream>

namespace Learning
{


	class Patron {
		friend std::ostream& operator<<(std::ostream& os, const Patron& patron);
		friend bool operator==(const Patron& lhs, const Patron& rhs);
		friend bool operator!=(const Patron& lhs, const Patron& rhs);
	public:
		Patron() = default;
		Patron(int cardNumber, double lateFee);

		int GetCardNumber() const { return mCardNumber; }
		double GetLateFee() const { return mLateFee; }
		void SetLateFee(double lateFee) { mLateFee = lateFee; }



	private:
		int mCardNumber{};
		double mLateFee{};
	};

	bool IsLateFee(Patron& patron);
} /*namespace Learning*/


#endif //CHAPTER09_PATRON_H

