/*
 * Created by Yves Gingras on 2018-11-21.
 *
 * The 'Learning' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#ifndef CHAPTER09_LIBRARY_H
#define CHAPTER09_LIBRARY_H

#include <vector>
#include "Book.h"
#include "Patron.h"
#include "../Chrono.h"

namespace Learning
{
	struct Transaction {
		Transaction();
		Transaction(const Book& book, const Patron& patron, const Chrono::Date& date);

		Book book{};
		Patron patron{};
		Chrono::Date date{};
	};

	class Library {
	public:
		void AddBook(Book& book);
		void AddPatron(Patron patron);
		void CheckOutBook(Patron& patron, Book& book, Chrono::Date& date);
		void DisplayIndebtedPatrons();
	private:

		std::vector<Book> mBooks;
		std::vector<Patron> mPatrons;
		std::vector<Transaction> mTransactions;
		void ValidateCheckOut(const Patron& patron, const Book& book);
	};
}/*namespace Learning*/
#endif //CHAPTER09_LIBRARY_H
