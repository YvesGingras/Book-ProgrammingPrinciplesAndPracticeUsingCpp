/*
 * Created by Yves Gingras on 2018-11-20.
 *
 * The 'Book' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#include "Patron.h"

namespace Library
{
	Patron::Patron(int cardNumber, double lateFee)
			: mCardNumber(cardNumber), mLateFee(lateFee) { }

	std::ostream& operator<<(std::ostream& os, const Patron& patron) {
		os << "\nCard Number: " << patron.mCardNumber
		   << "\nLate Fee: " << patron.mLateFee;
		return os;
	}

	bool IsLateFee(Patron& patron) { return patron.GetLateFee() != 0; }
}