/*
 * Created by Yves Gingras on 2018-11-21.
 *
 * The 'Learning' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#include <iostream>
#include "Library.h"

using namespace std;
using namespace Chrono;

namespace Learning
{
	Transaction::Transaction() = default;

	Transaction::Transaction(const Book& book, const Patron& patron, const Chrono::Date& date)
			: book(book), patron(patron), date(date) { }

	void Library::AddBook(Book& book) {
		mBooks.push_back(book);
	}

	void Library::AddPatron(Patron patron) {
		mPatrons.push_back(patron);
	}

	void Library::CheckOutBook(Patron& patron, Book& book, Date& date) {
		try {
			ValidateCheckOut(patron,book); // throws an Invalid exception if invalid

			book.CheckOut();
			mTransactions.emplace_back(book, patron, date);
		}
		catch (Invalid & e) {
			throw Invalid(e.m_errorMessage);
		}
		catch (...) {
			throw runtime_error("An unknown exception has occurred in 'MethodName'!\n"
			                    "Program is terminating...");
		}



	}

	void Library::DisplayIndebtedPatrons() {
		std::vector<Patron> indebtedPatrons;

		for (const auto& patron : mPatrons)
			if (patron.GetLateFee() > 0)
				indebtedPatrons.push_back(patron);

		if (indebtedPatrons.empty())
			cout << "\nNo user has a late fee to pay" << endl;
		else {
			cout << "\nThe following users have a late fee to pay." << endl;
			for (const auto& indebtedPatron : indebtedPatrons) {
				cout << "User card number: " << indebtedPatron.GetCardNumber()
				     << " , Fee amount: " << indebtedPatron.GetLateFee() << endl;
			}
		}
	}

	void Library::ValidateCheckOut(const Patron& patron, const Book& book) {
		bool patronPresent{false}, bookPresent{false};
		//first validation

		for (const auto& item : mPatrons)
			if (item.GetCardNumber() == patron.GetCardNumber()) patronPresent = true;

		for (const auto& mBook : mBooks)
			if (mBook.GetIsbn() == book.GetIsbn()) bookPresent = true;

		if (!(patronPresent))
			throw Invalid("CheckOutBook()\n"
			              "Error: User number '" + to_string(patron.GetCardNumber()) +
			              "' is not present in the library.");

		if (!(bookPresent))
			throw Invalid("CheckOutBook()\n"
			              "Error: book with ISBN number '" + book.GetIsbn() +
			              "' is not present in the library.");

		//second validation.
		if (patron.GetLateFee() != 0)
			throw Invalid("CheckOutBook()\n"
			              "Error: User '" + to_string(patron.GetCardNumber()) +
			              "' owes a fee of '" + to_string(patron.GetLateFee()));
	}
}/*namespace Learning*/