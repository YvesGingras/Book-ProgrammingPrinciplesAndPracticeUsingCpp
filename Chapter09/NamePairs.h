/*
 * Created by Yves Gingras on 2018-11-14.
 *
 * Chapter 9, exercises 2 & 3. The 'Person' class in this file is in fact the 'Name_pairs'
 * class as described in the book.
 *
 */

#ifndef CHAPTER09_PERSON_H
#define CHAPTER09_PERSON_H

#include <string>
#include <vector>

namespace NamePair
{
	class NamePairs {
		friend std::ostream& operator<<(std::ostream& outStream, NamePairs& namePairs);
		friend bool operator==(const NamePairs& namePairsLeft, const NamePairs& namePairsRight);
		friend bool operator!=(const NamePairs& namePairsLeft, const NamePairs& namePairsRight);
	public:
		void ReadNames();
		void Print();
	private:
		static constexpr char m_quit {'|'};
		std::vector<std::string> m_names{};
		std::vector<double> m_ages{};
		void ReadAges();
		void Sort();
		std::string Print(std::string dummy);
	};
}/*namespace NamePair*/
#endif //CHAPTER09_PERSON_H
