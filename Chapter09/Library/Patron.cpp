/*
 * Created by Yves Gingras on 2018-11-20.
 *
 * The 'Patron' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#include "Patron.h"

namespace Learning
{
	Patron::Patron(int cardNumber, double lateFee)
			: mCardNumber(cardNumber), mLateFee(lateFee) { }

	std::ostream& operator<<(std::ostream& os, const Patron& patron) {
		os << "\nCard Number: " << patron.mCardNumber
		   << "\nLate Fee: " << patron.mLateFee;
		return os;
	}


	bool operator==(const Learning::Patron& lhs, const Learning::Patron& rhs) {
		return lhs.mCardNumber == rhs.mCardNumber &&
		       lhs.mLateFee == rhs.mLateFee;
	}

	bool operator!=(const Learning::Patron& lhs, const Learning::Patron& rhs) {
		return !(rhs == lhs);
	}

	bool IsLateFee(Patron& patron) { return patron.GetLateFee() != 0; }
}