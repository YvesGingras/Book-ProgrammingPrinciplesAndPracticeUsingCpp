/*
 * Created by Yves Gingras on 2018-11-20.
 *
 * The 'Book' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#ifndef CHAPTER09_PATRON_H
#define CHAPTER09_PATRON_H

#include <ostream>

namespace Library
{
	class Patron {
		friend std::ostream& operator<<(std::ostream& os, const Patron& patron);

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
} /*namespace Library*/


#endif //CHAPTER09_PATRON_H
