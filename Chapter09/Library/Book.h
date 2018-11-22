/*
 * Created by Yves Gingras on 2018-11-16.
 *
 * The 'Book' class, which is part of the library 'project' that includes exercises 5, 6, 7, 8 & 9.
 */

#ifndef CHAPTER09_BOOK_H
#define CHAPTER09_BOOK_H

//#include <string>
#include <vector>
#include "../Chrono.h"

namespace Learning
{
	enum class Genre {
		ToDefine,
		Fiction,
		NonFiction,
		Periodical,
		Biography,
		Children,
	};

	class Invalid {
	public:
		Invalid(const std::string& errorMessage);
		std::string m_errorMessage{};
	};



	class Book {
		friend std::ostream& operator<<(std::ostream& inStream, Book& book);
		friend bool operator==(const Book& lhs, const Book& rhs);
		friend bool operator!=(const Book& lhs, const Book& rhs);

	public:
		Book();
		Book(const std::string& title, const std::string& author, const std::string& isbn,
				     const Chrono::Date& copyrightDate, Genre genre, bool isCheckedOut);

		const std::string& GetTitle() const { return mTitle; };
		const std::string& GetAuthor() const { return mAuthor; };
		const std::string& GetIsbn() const { return mIsbn; };
		const Chrono::Date& GetCopyrightDate() const { return mCopyrightDate; };
		Genre GetGenre() const;
		bool GetIsCheckedOut() const { return mIsCheckedOut; }
		void CheckIn();
		void CheckOut();

	private:
		std::string mTitle{};
		std::string mAuthor{};
		std::string mIsbn{};
		Chrono::Date mCopyrightDate{};
		Genre mGenre{};
		static const std::vector<std::string> mStringGenres;
		bool mIsCheckedOut{};
		bool IsIsbnValid(std::string isbn);
		static std::string GetStringGenre(Genre genre);
	};






} /*namespace Learning*/
#endif //CHAPTER09_BOOK_H
