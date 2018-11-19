/*
 * Created by Yves Gingras on 2018-11-16.
 *
 * The 'Book' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#ifndef CHAPTER09_BOOK_H
#define CHAPTER09_BOOK_H

//#include <string>
#include "Chrono.h"

namespace Library
{
	class Invalid {
	public:
		Invalid(const std::string& errorMessage);
		std::string m_errorMessage{};
	};

	class Book {
		friend bool operator==(const Book& lhs, const Book& rhs);
		friend bool operator!=(const Book& lhs, const Book& rhs);

	public:
		Book();
		Book(const std::string& title, const std::string& author, const std::string& isbn,
		        const Chrono::Date& copyrightDate, bool isCheckedOut);

		const std::string& GetTitle() const { return mTitle; };
		const std::string& GetAuthor() const { return mAuthor; };
		const std::string& GetIsbn() const { return mIsbn; };
		const Chrono::Date& GetCopyrightDate() const { return mCopyrightDate; };
		bool GetIsCheckedOut() const { return mIsCheckedOut; }
		void CheckIn();
		void CheckOut();

	private:
		std::string mTitle{};
		std::string mAuthor{};
		std::string mIsbn{};
		Chrono::Date mCopyrightDate{};
		bool mIsCheckedOut{};
		bool IsIsbnValid(std::string isbn);
	};

	std::ostream& operator<<(std::ostream& inStream, Book& book);



} /*namespace Library*/
#endif //CHAPTER09_BOOK_H
