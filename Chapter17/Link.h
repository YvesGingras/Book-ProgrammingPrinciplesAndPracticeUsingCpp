/*
 * Created by Yves Gingras on 2018-12-27.
 */

#ifndef CHAPTER17_LINK_H
#define CHAPTER17_LINK_H


#include <string>

namespace Gods
{
	struct God {
		std::string mName{"To define"};
		std::string mMythology{"To define"};
		std::string mVehicle{"To define"};
		std::string mWeapon{"To define"};
	};

	class Link {
	public:
		std::string mValue;
		God mGod{};

		Link(const std::string& value, Link* prev = nullptr, Link* succ = nullptr);

		Link* Insert(Link* newLink);

		Link* Add(Link* newLink);

		Link* Erase();

		Link* Find(const std::string& value);

		const Link* Find(const std::string& value) const;

		Link* Advance(int step) const;

		Link* Next() const { return mSuccessor; }

		Link* Previous() const { return mPredecessor; }

		Link* GetPredecessor() const { return mPredecessor; }

		Link* GetSuccessor() const { return mSuccessor; }

	private:
		Link* mPredecessor;
		Link* mSuccessor;

	};



	void PrintAll(Link* linkedList);

	void PrintAll2(Link* linkedList);
} /*Gods*/

#endif //CHAPTER17_LINK_H
