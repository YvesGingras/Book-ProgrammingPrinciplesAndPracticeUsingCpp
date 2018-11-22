/*
 * Created by Yves Gingras on 2018-11-16.
 *
 * The 'Book' class which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#include <sstream>
#include <iostream>
#include <cctype>
#include "Book.h"

using namespace std;

namespace Learning
{
	const std::vector<std::string> Book::mStringGenres{"ToDefine", "Fiction", "NonFiction",
	                                             "Periodical", "Biography", "Children"};

	Book::Book() : mTitle("title"), mAuthor("author name"), mIsbn("isbn") { }

	Book::Book(const std::string& title, const std::string& author, const std::string& isbn,
	           const Chrono::Date& copyrightDate, Genre genre, bool isCheckedOut)
			: mTitle(title), mAuthor(author), mIsbn(isbn),
			  mCopyrightDate(copyrightDate),
			  mGenre(genre),
			  mIsCheckedOut(isCheckedOut) {
		if (!IsIsbnValid(isbn))
			throw Invalid("\nBook(string,string,string,Date,bool)\n"
			              "Error: Invalid ISBN '" + isbn + "'");
	};

	bool Book::IsIsbnValid(std::string isbn) {
		constexpr int dashesQty{4};
		constexpr char dash{'-'};
		int dashCounter{};
		for (const auto& item : isbn)
			if (item == dash)
				dashCounter++;

		if (dashCounter != dashesQty)
			return false;

		//testing inputs between the '-'s.
		int number1{}, number2{}, number3{}, number4{};
		string lastDigit{};

		try {
			stringstream stringStreamIsbn{isbn};
			int isbnInteger{};
			string isbnString{};

			dashCounter = 0;
			while (stringStreamIsbn) {
				if (dashCounter != 4)
					stringStreamIsbn >> isbnInteger;
				else {
					stringStreamIsbn >> isbnString;
					lastDigit = (isbnString);
				};

				if (stringStreamIsbn.peek() == dash) {
					dashCounter++;
					switch (dashCounter) {
						case 1:
							number1 = isbnInteger;
							break;
						case 2:
							number2 = isbnInteger;
							break;
						case 3:
							number3 = isbnInteger;
							break;
						default: // dashCounter == 4
							number4 = isbnInteger;
							break;
					}
					stringStreamIsbn.get();
				}
			}
			if (dashCounter != dashesQty) {
				return false; //looping interrupted trying ot assign non integer to 'isbnInteger'
			}

			// last test to an eventual 'true'.
			return isalpha(lastDigit[0]) || isdigit(static_cast<unsigned char>(lastDigit[0]));
		}
		catch (Invalid& e) {
			throw runtime_error("An exception has occurred in 'IsIsbnValid(string)': \n"
			                    "Error: " + e.m_errorMessage);
		}
	}

	void Book::CheckIn() {
		if (!mIsCheckedOut)
			throw Invalid("CheckIn(Book)\n"
			              "Error: book '" + GetTitle() + "' is already checked in.");

		mIsCheckedOut = false;
	}

	void Book::CheckOut() {
		if (mIsCheckedOut)
			throw Invalid("CheckIn(Book)\n"
			              "Error: book '" + GetTitle() + "' is already checked out.");

		mIsCheckedOut = true;
	}

	Genre Book::GetGenre() const {
		return mGenre;
	}

	bool operator==(const Book& lhs, const Book& rhs) {
		return lhs.mIsbn == rhs.mIsbn;
	}

	bool operator!=(const Book& lhs, const Book& rhs) {
		return !(rhs == lhs);
	}

	ostream& operator<<(ostream& outStream, Book& book) {
		string isCheckedOut{book.GetIsCheckedOut() ? "true" : "false"};
		string date{to_string(book.GetCopyrightDate().GetYear())
		            + ',' + to_string(int(book.GetCopyrightDate().GetMonth()))
		            + ',' + to_string(book.GetCopyrightDate().GetDay())};

		string genre = Book::GetStringGenre(book.GetGenre());

		return outStream << "\nBook's specifications:"
		                    "\n  Title: " + book.GetTitle() +
		                    "\n  Author: " + book.GetAuthor() +
		                    "\n  ISBN: " + book.GetIsbn() +
		                    "\n  Copyright Date: " + date +
		                    "\n  Genre: " + genre +
		                    "\n  Checked Out Status: " + isCheckedOut;
	}

	std::string Book::GetStringGenre(Genre genre) {
		return mStringGenres[(int) genre];
	}

	Invalid::Invalid(const string& errorMessage)
			: m_errorMessage(errorMessage) { }

}/*namespace Learning*/
