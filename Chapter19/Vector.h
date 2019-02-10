/*
 * Created by Yves Gingras on 2019-01-19.
 */

#ifndef CHAPTER19_VECTOR_H
#define CHAPTER19_VECTOR_H

#include <initializer_list>
#include <algorithm>
#include <memory>

/*
	//Does not work without de function wich I can't find in the book's material.
    //Using the 'std::allocator' class instead.

template<class T>
class Allocator {
	T* Allocate(int qtyObjects);
	void DeAllocate(T* begin, int qtyObjects);

	void Construct(T* object, const T& value);
	void Destroy(T* object);
};
*/


template<class T, class A = std::allocator<T>>
class Vector {
public:

	//default constructor
	Vector()
			: mSize{0}, mElements{nullptr}, mSpace{0} {
		/*...*/
	}

	//basic constructor
	explicit Vector(int size) : mSize{size},
	                            mElements{new T[mSize]},  //uninitialized memory for elements...
	                            mSpace{size} {
		for (int i = 0; i < mSize; ++i)
			mElements[i] = T(); //...initializing now
	}

	//initializer-list constructor
	Vector(std::initializer_list<T> initializerList);

	//copy constructor
	Vector(const Vector& copiedVector);

	//move constructor
	Vector(Vector&& movedVector);

	//move assignment
	Vector& operator=(Vector& assignedVector);

	//Destructor
	~Vector() {
		delete[] mElements;
	};

	//Access content through subscript annotation. Non 'const' vectors
	T& operator[](int subscript) {
		return mElements[subscript];
	}

	//Access content through subscript annotation. 'Const' vectors.
	T operator[](int subscript) const {
		return mElements[subscript];
	}

	//Reading size
	int Size() const {
		return mSize;
	}

	//reading space
	int Capacity() const {
		return mSpace;
	}

	//adding and initializing newsize elements
	void Resize(int newSize, T defaultValue = T());

	//adding memory space for new elements
	void Reserve(int newAllocation);

	//Adding a new element
	void PushBack(const T& newElement);

public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
	A mAllocator;
	int mSize;
	T* mElements;
	int mSpace;
};

template<class T, class A>
//void Vector<T,A>::PushBack(const T newElement) {
void Vector<T,A>::PushBack(const T& newElement) {
	if (mSpace == 0)
		Reserve(8);
	else if (mSize == mSpace)
		Reserve(mSpace * 2);

//	mElements[mSize] = newElement;
	mAllocator.construct(&mElements[mSize],newElement);
	++mSize;
}

template<class T, class A>
void Vector<T,A>::Reserve(int newAllocation) {
	if (newAllocation <= mSpace)
		return;

//	T* tempPointer = new T[newAllocation];
	T* tempPointer = mAllocator.allocate(newAllocation);

	for (int i = 0; i < mSize; ++i)
//		tempPointer[i] = mElements[i];
		mAllocator.construct(&tempPointer[i],mElements[i]); //copy

	for (int i = 0; i < mSize; ++i)
		mAllocator.destroy(&mElements[i]); //destroy

	mAllocator.deallocate(mElements,mSpace);
//	delete[] mElements;
	mElements = tempPointer;
	mSpace = newAllocation;
}

template<class T, class A>
void Vector<T,A>::Resize(int newSize, T defaultValue) {
	Reserve(newSize);

	for (int i = mSize; i < newSize; ++i)
//		mElements[i] = defaultValue;
		mAllocator.construct(&mElements[i],defaultValue);

	for (int i = newSize; i < mSize; ++i)
		mAllocator.destroy(&mElements[i]);

	mSize = newSize;
}

template<class T, class A>
Vector<T,A>::Vector(std::initializer_list<T> initializerList)
		: mSize{static_cast<int>(initializerList.size())},
		  mElements{new T[mSize]}, //uninitialized memory for elements...
		  mSpace{mSize} {
	std::copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
}


#endif //CHAPTER19_VECTOR_H
