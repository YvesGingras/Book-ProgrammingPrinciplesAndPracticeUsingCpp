/*
 * Created by Yves Gingras on 2018-11-14.
 *
 * Chapter 9, exercises 2 & 3. The 'Person' class in this file is in fact the 'Name_pairs'
 * class as described in the book.
 *
 */

#include "NamePairs.h"
#include <iostream>

using namespace std;

namespace NamePair
{
	void NamePairs::ReadNames() {
		auto isFirstLoopDone{false};
		cout << "Type the person's name followed by 'enter'.\n"
		        "or type '|' if you are done: " << endl;

		char input{};
		while (input != m_quit)  {
			string name{};
			if (isFirstLoopDone)
				cout << "Next name: " << endl;

			while (cin) {
				if (cin.peek() == '\n') {
					cin.get();
					break;
				}
				cin >> input;
				name += input;
			}

			if (name != "|")
				m_names.push_back(name);
			isFirstLoopDone = true;
		}
		ReadAges();
	}

	void NamePairs::ReadAges() {
		cout << "\nType each person's age followed by 'enter'. " << endl;

		for (const auto& name : m_names) {
			cout << "Enter " << name << "'s age: " << endl;

			double age{};
			while (cin) {
				int input{};
				if (cin.peek() == '\n') {
					cin.get();
					break;
				}

				cin >> input;
				age += input;
			}
			m_ages.push_back(age);
		}
	}

	void NamePairs::Print() {
		Sort();

		cout << '\n'
		     << "The name/age pairs are:\n";

		for (int i = 0; i < m_names.size(); ++i) {
			cout << "Name: " << m_names[i] << " - Age: " << m_ages[i] << endl;
		}
	}

	string NamePairs::Print(string dummy = "Exercise4") {
		string output{};
		Sort();

		cout << '\n'
		     << "The name/age pairs are:\n";

		for (int i = 0; i < m_names.size(); ++i) {
			output += "Name: " + m_names[i] + " - Age: " + to_string(int(m_ages[i])) + '\n';
		}
		return output;
	}

	void NamePairs::Sort() {
		string biggerName{};
		double swappedAge{};
		for (int i = 0; i < m_names.size(); ++i) {
			for (int j = i; j < m_names.size(); ++j) {
				if (m_names[j] < m_names[i]) {
					biggerName = m_names[i];
					swappedAge = m_ages[i];
					m_names[i] = m_names[j];
					m_ages[i] = m_ages[j];
					m_names[j] = biggerName;
					m_ages[j] = swappedAge;
				}
		    }
		}
	}

	ostream& operator<<(ostream& outStream, NamePairs& namePairs) {
		return outStream << namePairs.Print("Exercise4") ;
	}

	bool operator==(const NamePairs& namePairsLeft, const NamePairs& namePairsRight) {
		for (int i = 0; i < namePairsLeft.m_names.size(); ++i)
			if ((namePairsLeft.m_names[i] != namePairsRight.m_names[i]) ||
				    (namePairsLeft.m_ages[i] != namePairsRight.m_ages[i]))
				return false;
		return true;
	}

	bool operator!=(const NamePairs& namePairsLeft, const NamePairs& namePairsRight) {
		return !(namePairsLeft == namePairsRight);
	}
} /*namespace NamePair*/