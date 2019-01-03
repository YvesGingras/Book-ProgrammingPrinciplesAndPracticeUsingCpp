/*
 * Created by Yves Gingras on 2018-12-27.
 */

#include <iostream>
#include "Link.h"

using namespace std;

namespace Gods
{
	Link::Link(const std::string& value, Link* prev, Link* succ)
			: mValue{value}, mPredecessor{prev}, mSuccessor{succ} {
		mGod.mName = mValue;}

	Link* Link::Insert(Link* newLink) {
		if (newLink == nullptr)
			return this;

		/*
		if (this == nullptr)
			return newLink;
		*/

		newLink->mSuccessor = this; //newLink is placed 'before' currentLink.

		if (mPredecessor) //if currentLink has a predecessor Link...
			mPredecessor->mSuccessor = newLink; //...its Successor becomes newLink (instead of currentLink)

		newLink->mPredecessor = mPredecessor; // currentLink Predecessor becomes newLink Predecessor.
		mPredecessor = newLink; // newLink become currentLink Predecessor.

		return newLink;
	}

	Link* Link::Add(Link* newLink) {
		if (newLink == nullptr)
			return this;

		/*
		if (currentLink == nullptr)
			return newLink;
		*/

		newLink->mPredecessor = this; //newLink is placed 'after' currentLink.

		if (mSuccessor) //if currentLink has a successor Link...
			mSuccessor->mPredecessor = newLink; //...its Predecessor becomes newLink (instead of currentLink)

		newLink->mSuccessor = mSuccessor; // currentLink Successor becomes newLink Successor.
		mSuccessor = newLink; // newLink become currentLink Successor.

		return newLink;
	}

	Link* Link::Erase() {
		/*
		if (currentPointer == nullptr)
			return nullptr;
		*/

		// and pointers fiddling...
		if (mSuccessor) // if currentPointer has a successor...
			mSuccessor->mPredecessor = mPredecessor; /* .. its predecessor becomes
                                                                                  * currentPointer predecessor.s*/

		if (mPredecessor)
			mPredecessor->mSuccessor = mSuccessor;

		return mSuccessor;
	}

	Link* Link::Find(const std::string& value) {
		Link* testPointer = this;

		while (testPointer) {
			if (testPointer->mValue == value)
				return testPointer;

			testPointer = testPointer->mSuccessor;
		}

		return nullptr;
	}

	const Link* Link::Find(const string& value) const {
		const Link* testPointer = this;

		while (testPointer) {
			if (testPointer->mValue == value)
				return testPointer;

			testPointer = testPointer->mSuccessor;
		}

		return nullptr;
	}

	Link* Link::Advance(int step) const {
		/*
		if (currentPointer == nullptr)
			return nullptr;
		*/
		Link* currentPointer = new Link{""};

		if (0<step) { /*moves forward.*/
			while (step--) {
				if (mSuccessor == nullptr)
					return nullptr;

				currentPointer = mSuccessor;
			}
		}
		else if (step < 0) { /*negatives steps*/
			while (step++) {
				if (mPredecessor == nullptr)
					return nullptr;

				currentPointer = mPredecessor;
			}
		}

		return currentPointer;
	}

	void PrintAll(Link* linkedList) {
		cout << "{ ";
		while (linkedList) {
			cout << linkedList->mValue << flush;
			if (linkedList->Next() != nullptr)
				cout << ", ";

			linkedList = linkedList->Next();
		}
		cout << " }";


	}

	void PrintAll2(Link* linkedList) {
		while (linkedList) {
			cout << linkedList->mValue
			     << "\n\t" << "Mythology: " << linkedList->mGod.mMythology
				 << "\n\t" << "Vehicle: " << linkedList->mGod.mVehicle
				 << "\n\t" << "Weapon: " << linkedList->mGod.mWeapon << endl;

			linkedList = linkedList->Next();
		}
	}
} /*Gods*/