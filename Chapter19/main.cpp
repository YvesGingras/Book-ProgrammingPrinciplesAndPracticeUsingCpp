#include <iostream>
#include <vector>
#include "Vector.h"
#include "GraphFiles/Point.h"
#include "GraphFiles/Graph.h"

using namespace Graph_lib;
using namespace std;

/*Utility*/
void FirstLine(const string& name) {
	cout << "\n*" << name << "*" << endl;
}

void LastLine() {
	cout << "----------------------------------\n";
}

void PrintIntArray(ostream& outStream, int* a, int qtyElements) {
	for (int i = 0; i < qtyElements; ++i)
		outStream << "array[" << to_string(i) << "] = " << a[i] << endl;
}

void PrintDoubleArray(ostream& outStream, double* a, int qtyElements) {
	for (int i = 0; i < qtyElements; ++i)
		outStream << "array[" << to_string(i) << "] = " << a[i] << endl;
}

void PrintIntVector(ostream& outStream, const vector<int>& passedVector) {
	for (int i = 0; i < passedVector.size(); ++i)
		outStream << "vector[" << to_string(i) << "] = " << passedVector[i] << endl;
}

void PrintCString(ostream& outStream, const char* cString) {
	if (*cString == '\0') {
		outStream << "CStyle string is empty; nothing to print!" << endl;
		return;
	}

	for (int i = 0; cString[i] != '\0'; ++i) {
		outStream << cString[i];
	}

	outStream << endl;
}
/***********************************************/

/*Declaration/Definition - BEGIN*/

//used in **Example 19_3_5**
template<typename T, int N>
struct Array {
	T elements[N]; //array

	//acces: return reference
	T& operator[](int n) {
		return elements[n];
	}

	const T& operator[](int n) const {
		return elements[n];
	}

	//conversion to T*
	T* Data() {
		return elements;
	}

	const T* Data() const {
		return elements;
	}

	int Size() const {
		return N;
	}
};

template<class T, int N>
void Fill(Array<T, N>& buffer, const T& value) {
	for (int i = 0; i < N; ++i) {
		buffer[i] = value;
	}
}

template<class C>
void PrintOut(const C& c, string header) {

	cout << '\n' << header << '\n';

	for (int i = 0; i < c.Size(); ++i) {
		cout << "\tContainer[" << i << "] : " << c[i] << '\n';
	}
}

//Global declarations
Array<int, 256> gb;
Array<double, 6> ad{0.0, 1.1, 2.2, 3.3, 4.4, 5.5};
const int maxSize = 1024;

void SomeFunction(int n) {
	Array<char, maxSize> local{};

//	Array<char,n> oops;
	Array<char, maxSize> local2 = local;

//	double* p =ad; //error; no implicit conversion to pointer.
	double* q = ad.Data(); //Ok; explicit conversion.


	cout << "";
}

//used in **Example 19_3_6**
struct NoDefault {
	NoDefault() = default;; //can't make work without a default constructor (?!)
	explicit NoDefault(int integerValue) { };
};

/*Declaration/Definition - END*/
/***********************************************/
/*Examples*/

//Changing size
void Example19_2_1() {
	class Vector19_2_1 {
	public:
		//default constructor
		Vector19_2_1()
				: mSize{0}, mElements{nullptr}, mSpace{0} {
			/*...*/
		}

		//basic constructor
		explicit Vector19_2_1(int size)
				: mSize{size},
				  mElements{new double[mSize]}, //uninitialized memory for elements...
				  mSpace{size} {
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector19_2_1(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]}, //uninitialized memory for elements...
				  mSpace{mSize} {
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector19_2_1(const Vector19_2_1& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]}, //uninitialized memory for elements...
				  mSpace{mSize} {
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector19_2_1() {
			delete[] mElements;
		}

		//Copy Assignment
		Vector19_2_1& operator=(const Vector19_2_1& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;
			mSpace = assignedVector.mSpace;

			return *this;
		}

		//to access content through subscript annotation. Non 'const' vectors
		double& operator[](int n) {
			return mElements[n]; //returns reference
		}

		//to access content through subscript annotation. 'Const' vectors.
		double operator[](int n) const {
			return mElements[n]; //returns reference
		}


	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
		int mSpace;
	};

	//testing member default initialization (in debug mode...)
	FirstLine("Example19_2_1()");
	cout << "\nDefault initialization.\n";

	Vector19_2_1 vector19_2_1(1);
	cout << "Size: " << vector19_2_1.mSize << '\n'
	     << "Elements: " << vector19_2_1.mElements << '\n'
	     << "Space: " << vector19_2_1.mSpace << '\n';


	LastLine();

}

//Adding Reserve & Capacity member methods
void Example19_2_2() {
	class Vector19_2_2 {
	public:
		//default constructor
		Vector19_2_2()
				: mSize{0}, mElements{nullptr}, mSpace{0} {
			/*...*/
		}

		//basic constructor
		explicit Vector19_2_2(int size)
				: mSize{size},
				  mElements{new double[mSize]},  //uninitialized memory for elements...
				  mSpace{size} {
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector19_2_2(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]}, //uninitialized memory for elements...
				  mSpace{mSize} {
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector19_2_2(const Vector19_2_2& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]}, //uninitialized memory for elements...
				  mSpace{mSize} {
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector19_2_2() {
			delete[] mElements;
		}

		//adding memory space for new elements
		void Reserve(int newAllocation) {
			if (newAllocation <= mSpace)
				return;

			auto* tempPointer = new double[newAllocation];
			for (int i = 0; i < mSize; ++i)
				tempPointer[i] = mElements[i];

			delete[] mElements;
			mElements = tempPointer;
			mSpace = newAllocation;
		}

		//reading space
		int Capacity() {
			return mSpace;
		}

		//Copy Assignment
		Vector19_2_2& operator=(const Vector19_2_2& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;
			mSpace = assignedVector.mSpace;

			return *this;
		}

		//to access content through subscript annotation. Non 'const' vectors
		double& operator[](int n) {
			return mElements[n]; //returns reference
		}

		//to access content through subscript annotation. 'Const' vectors.
		double operator[](int n) const {
			return mElements[n]; //returns reference
		}


	private: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
		int mSpace;
	};

	//testing member default initialization (in debug mode...)
	FirstLine("Example19_2_2()");
	cout << "\nReserving and then reading 'memory capacity'.\n";

	Vector19_2_2 vector19_2_2(1);

	int newCapacity{10};
	cout << "Enter an integer for the new memory capacity: " << newCapacity << '\n';
//	cin >> newCapacity;

	vector19_2_2.Reserve(newCapacity);

	cout << "Capacity: " << vector19_2_2.Capacity() << '\n';



	LastLine();
}

//Adding Resizing
void Example19_2_3() {
	class Vector19_2_3 {
	public:
		//default constructor
		Vector19_2_3()
				: mSize{0}, mElements{nullptr}, mSpace{0} {
			/*...*/
		}

		//basic constructor
		explicit Vector19_2_3(int size)
				: mSize{size},
				  mElements{new double[mSize]}, //uninitialized memory for elements...
				  mSpace{size} {
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector19_2_3(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]}, //uninitialized memory for elements...
				  mSpace{mSize} {
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector19_2_3(const Vector19_2_3& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]}, //uninitialized memory for elements...
				  mSpace{mSize} {
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}


		//Destructor
		~Vector19_2_3() {
			delete[] mElements;
		}

		//adding and initializing newsize elements
		void Resize(int newSize) {
			Reserve(newSize);

			for (int i = mSize; i < newSize; ++i)
				mElements[i] = 0;
			mSize = newSize;
		}

		//adding memory space for new elements
		void Reserve(int newAllocation) {
			if (newAllocation <= mSpace)
				return;

			auto* tempPointer = new double[newAllocation];
			for (int i = 0; i < mSize; ++i)
				tempPointer[i] = mElements[i];

			delete[] mElements;
			mElements = tempPointer;
			mSpace = newAllocation;
		}

		//reading space
		int Capacity() {
			return mSpace;
		}

		//Copy Assignment
		Vector19_2_3& operator=(const Vector19_2_3& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;
			mSpace = assignedVector.mSpace;

			return *this;
		}

		//to access content through subscript annotation. Non 'const' vectors
		double& operator[](int n) {
			return mElements[n]; //returns reference
		}

		//to access content through subscript annotation. 'Const' vectors.
		double operator[](int n) const {
			return mElements[n]; //returns reference
		}


	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
		int mSpace;
	};

	//testing member default initialization (in debug mode...)
	FirstLine("Example19_2_3()");
	cout << "\nResizing and initializing the vector's elements.\n";

	Vector19_2_3 vector19_2_3{19.23};

	int newSize{10};
	cout << "Initial values:" << '\n';
//	cin >> newSize;

	vector19_2_3.Resize(newSize);
	cout << "\tSize: " << vector19_2_3.mSize << '\n'
	     << "\tCapacity: " << vector19_2_3.Capacity() << '\n';


	/*TryThis19_2_3 - Begin*/
	cout << "\nTryThis '19_2_3'" << '\n';

	newSize = 0;
	cout << "Enter an integer for the newsize: " << newSize << '\n';
//	cin >> newSize;

	vector19_2_3.Resize(newSize);
	cout << "Size: " << vector19_2_3.mSize << '\n'
	     << "Capacity: " << vector19_2_3.Capacity() << '\n';


	newSize = -77;
	cout << "\nEnter an integer for the newsize: " << newSize << '\n';
//	cin >> newSize;

	vector19_2_3.Resize(newSize);
	cout << "Size: " << vector19_2_3.mSize << '\n'
	     << "Capacity: " << vector19_2_3.Capacity() << '\n';

	newSize = 100;
	cout << "\nEnter an integer for the newsize: " << newSize << '\n';
//	cin >> newSize;

	vector19_2_3.Resize(newSize);
	cout << "Size: " << vector19_2_3.mSize << '\n'
	     << "Capacity: " << vector19_2_3.Capacity() << '\n';



	/*TryThis19_2_3 - End*/

	LastLine();
}

//Adding 'PushBack'
void Example19_2_4() {
	class Vector19_2_4 {
	public:
		//default constructor
		Vector19_2_4()
				: mSize{0}, mElements{nullptr}, mSpace{0} {
			/*...*/
		}

		//basic constructor
		explicit Vector19_2_4(int size)
				: mSize{size},
				  mElements{new double[mSize]},  //uninitialized memory for elements...
				  mSpace{size} {
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector19_2_4(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector19_2_4(const Vector19_2_4& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]} { //uninitialized memory for elements...
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector19_2_4() {
			delete[] mElements;
		}

		//Adding a new element
		void PushBack(double newElement) {
			if (mSpace == 0)
				Reserve(8);
			else if (mSize == mSpace)
				Reserve(mSpace * 2);

			mElements[mSize] = newElement;
			++mSize;
		}

		//adding and initializing newsize elements
		void Resize(int newSize) {
			Reserve(newSize);

			for (int i = mSize; i < newSize; ++i)
				mElements[i] = 0;
			mSize = newSize;
		}

		//adding memory space for new elements
		void Reserve(int newAllocation) {
			if (newAllocation <= mSpace)
				return;

			auto* tempPointer = new double[newAllocation];
			for (int i = 0; i < mSize; ++i)
				tempPointer[i] = mElements[i];

			delete[] mElements;
			mElements = tempPointer;
			mSpace = newAllocation;
		}

		//reading space
		int Capacity() {
			return mSpace;
		}

		//Copy Assignment
		Vector19_2_4& operator=(const Vector19_2_4& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;
			mSpace = assignedVector.mSpace;

			return *this;
		}

		//to access content through subscript annotation. Non 'const' vectors
		double& operator[](int n) {
			return mElements[n]; //returns reference
		}

		//to access content through subscript annotation. 'Const' vectors.
		double operator[](int n) const {
			return mElements[n]; //returns reference
		}


	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
		int mSpace;
	};

	//testing member default initialization (in debug mode...)
	FirstLine("Example19_2_4()");
	cout << "\nAdding new elements to the vector.\n";

	Vector19_2_4 vector19_2_4;

	cout << "Initial values:" << '\n';
	cout << "\tSize: " << vector19_2_4.mSize << '\n'
	     << "\tCapacity: " << vector19_2_4.Capacity() << '\n'
	     << "\tElements address: " << vector19_2_4.mElements << '\n';


	auto newElement{2.25};
	cout << "\nEnter a double for the new element: " << newElement << '\n';
//	cin >> newElement;
	vector19_2_4.PushBack(newElement);

	cout << "The 'Vector' content:\n";
	cout << "\tSize: " << vector19_2_4.mSize << '\n'
	     << "\tCapacity: " << vector19_2_4.Capacity() << '\n'
	     << "\tElements address: " << vector19_2_4.mElements << '\n';
	for (int j = 0; j < vector19_2_4.mSize; ++j) {
		cout << "\tElement[" << j << "] = " << vector19_2_4.mElements[j] << '\n';
	}

	newElement = 3.125;
	cout << "\nEnter a double for the new element: " << newElement << '\n';
//	cin >> newElement;
	vector19_2_4.PushBack(newElement);

	cout << "The 'Vector' content:\n";
	cout << "\tSize: " << vector19_2_4.mSize << '\n'
	     << "\tCapacity: " << vector19_2_4.Capacity() << '\n'
	     << "\tElements address: " << vector19_2_4.mElements << '\n';
	for (int j = 0; j < vector19_2_4.mSize; ++j) {
		cout << "\tElement[" << j << "] = " << vector19_2_4.mElements[j] << '\n';
	}

/*

//	TryThis19_2_3 - Begin
	cout << "\nTryThis '19_2_3'" << '\n';

	newSize = 0;
	cout << "Enter an integer for the newsize: " << newSize << '\n';
//	cin >> newSize;

	vector19_2_4.Resize(newSize);
	cout << "Size: " << vector19_2_4.mSize << '\n'
	     << "Capacity: " << vector19_2_4.Capacity() << '\n';


	newSize = -77;
	cout << "\nEnter an integer for the newsize: " << newSize << '\n';
//	cin >> newSize;

	vector19_2_4.Resize(newSize);
	cout << "Size: " << vector19_2_4.mSize << '\n'
	     << "Capacity: " << vector19_2_4.Capacity() << '\n';

	newSize = 100;
	cout << "\nEnter an integer for the newsize: " << newSize << '\n';
//	cin >> newSize;

	vector19_2_4.Resize(newSize);
	cout << "Size: " << vector19_2_4.mSize << '\n'
	     << "Capacity: " << vector19_2_4.Capacity() << '\n';
*/



	/*TryThis19_2_3 - End*/

	LastLine();
}

void Example19_3_1() {


	//testing member default initialization (in debug mode...)
	FirstLine("Example19_3_1()");
	cout << "\nTesting 'Template' style Vector.\n";

	Vector<int> vectorInts(2);
	cout << "\n**Vector contains 'int's.\n";
	cout << "Initial values:" << '\n';
	cout << "\tSize: " << vectorInts.mSize << '\n'
	     << "\tCapacity: " << vectorInts.Capacity() << '\n'
	     << "\tElements address: " << vectorInts.mElements << '\n';

	auto newintElement{2};
	cout << "\nEnter a integer for the new element: " << newintElement << '\n';
//	cin >> newintElement;
	vectorInts.PushBack(newintElement);

	Vector<int>* vectorIntAddress = &vectorInts;
	cout << "The 'Vector' content:\n";
	cout << "\tVector's address: " << vectorIntAddress << '\n'
	     << "\tSize: " << vectorInts.mSize << '\n'
	     << "\tCapacity: " << vectorInts.Capacity() << '\n'
	     << "\t'mElements' address: " << vectorInts.mElements << '\n';
	for (int j = 0; j < vectorInts.mSize; ++j) {
		cout << "\tElement[" << j << "] = " << vectorInts.mElements[j] << '\n';
	}

	//**
	Vector<double> vectorDoubles;
	cout << "\n**Vector contains 'double's.\n";
	cout << "Initial values:" << '\n';
	cout << "\tSize: " << vectorDoubles.mSize << '\n'
	     << "\tCapacity: " << vectorDoubles.Capacity() << '\n'
	     << "\tElements address: " << vectorDoubles.mElements << '\n';


	auto newDoubleElement{3.18};
	cout << "\nEnter a double for the new element: " << newDoubleElement << '\n';
//	cin >> newDoubleElement;
	vectorDoubles.PushBack(newDoubleElement);

	Vector<double>* vectorDoubleAddress = &vectorDoubles;
	cout << "The 'Vector' content:\n";
	cout << "\tVector's address: " << vectorDoubleAddress << '\n'
	     << "\tSize: " << vectorDoubles.mSize << '\n'
	     << "\tCapacity: " << vectorDoubles.Capacity() << '\n'
	     << "\t'mElements' address: " << vectorDoubles.mElements << '\n';
	for (int j = 0; j < vectorDoubles.mSize; ++j) {
		cout << "\tElement[" << j << "] = " << vectorDoubles.mElements[j] << '\n';
	}

	LastLine();
}

void Example19_3_4() {
	FirstLine("Example19_3_4()");

	cout << "\nTesting 'Containers and inheritance' compiler error (see code).\n";
	//std library vector
	vector<Shape> shapes;
	vector<Circle> circles;
//	shapes = circles; // error

/****/

	//std library vector
	vector<Shape*> shapesPointer;
	vector<Circle*> circlesPointer;
//	shapesPointer = circlesPointer;

	LastLine();
}

//Integers as template parameters
void Example19_3_5() {
	FirstLine("Example19_3_5()");
	cout << "\nTesting 'Integers as template parameters'.\n";

	Array<char, 5> buffer{};
	Fill(buffer, 'x'); // Fill() definition at top of the file...
	cout << "\n**First Array contains 'char's.\n";

	Array<char, 5>* bufferPointer = &buffer;
	cout << "The 'Array' content:\n";
	cout << "\tArray's address: " << bufferPointer << '\n'
	     << "\tSize: " << buffer.Size() << '\n'
	     << "\t'elements' address: " << &buffer.elements << '\n'
	     << "\tData: " << buffer.Data() << '\n';

	for (int i = 0; i < buffer.Size(); ++i) {
		cout << "\tArray[" << i << "] : " << buffer[i] << '\n';
	}

	//**
	Array<double, 10> buffer2{};
	Fill(buffer2, 0.125);
	cout << "\n**Second Array contains 'double's.\n";

	Array<double, 10>* buffer2Pointer = &buffer2;
	cout << "The 'Array' content:\n";
	cout << "\tArray's address: " << buffer2Pointer << '\n'
	     << "\tSize: " << buffer2.Size() << '\n'
	     << "\t'elements' address: " << &buffer2.elements << '\n'
	     << "\tData: " << buffer2.Data() << '\n';

	for (int i = 0; i < buffer2.Size(); ++i) {
		cout << "\tArray[" << i << "] : " << buffer2[i] << '\n';
	}

	//** - As define at end of section 19_3_5. See definition at top of the file...
	SomeFunction(0); // only for observing function content in debug...

	//** Demonstrating generic programming...
	PrintOut(ad, "From 'PrintOut' function; using an 'Array<char,int>'.");

	Vector<int> vi{5, 6, 7, 8, 9, 10};
	PrintOut(vi, "From ' PrintOut' function; using a 'Vector<int>'.");

	LastLine();
}

void Example19_3_7() {
	FirstLine("Example19_3_7()");
	cout << "Generalizing Vector.\n";
	cout << "\n**Supply a default value for the 'T' parameter.\n";

	Vector<double> vector1;
	cout << "\n'Vector': 'vector1.resize(3).\n";
	vector1.Resize(3);

	Vector<double>* vector1Address = &vector1;
	cout << "The 'Vector' content:\n";
	cout << "\tVector's address: " << vector1Address << '\n'
	     << "\tSize: " << vector1.mSize << '\n'
	     << "\tCapacity: " << vector1.Capacity() << '\n'
	     << "\t'mElements' address: " << vector1.mElements << '\n';
	for (int j = 0; j < vector1.mSize; ++j) {
		cout << "\tElement[" << j << "] = " << vector1.mElements[j] << '\n';
	}

	//**
	cout << "\n'Vector': 'vector1.resize(5, 2.125).\n";
	vector1.Resize(5, 2.125);

	vector1Address = &vector1;
	cout << "The 'Vector' content:\n";
	cout << "\tVector's address: " << vector1Address << '\n'
	     << "\tSize: " << vector1.mSize << '\n'
	     << "\tCapacity: " << vector1.Capacity() << '\n'
	     << "\t'mElements' address: " << vector1.mElements << '\n';
	for (int j = 0; j < vector1.mSize; ++j) {
		cout << "\tElement[" << j << "] = " << vector1.mElements[j] << '\n';
	}

	//** Trying to do the same demonstration as above, with a custom class without a default constructor.
//	Vector<NoDefault> vector2(10); //demonstrating that this will not compile, 'NoDefault' does not have default constructor

	NoDefault noDefault(2);
	NoDefault* noDefaultPointer = new NoDefault(2);

	Vector<NoDefault> vector3;
	vector3.Resize(5, NoDefault(2)); // can't make it work without adding a default constructor to 'NoDefault'.
	vector3.Resize(200);

	//** Dealing with the 'destructor' in relation with uninitialized data.


	LastLine();
}

void ExampleTemplate() {
	FirstLine("0ExampleTemplate()");
	cout << "\nBlaBla.\n";


	LastLine();
}

/***********************************************/
/*Drill*/
template<class T>
struct DrillStructure {
	explicit DrillStructure(T value)
			: mValue(value) { }

	T& GetValue() {
		return mValue;
	}

	void SetValue(T newValue) {
		mValue = newValue;
	}

private:
	T mValue;

};

//Drill #6
template<class T>
T& Get(DrillStructure<T>& drillStructure) {
	return drillStructure.GetValue();
}

//Drill #9
template<class T>
void Set(DrillStructure<T>& drillStructure, T newValue) {
	drillStructure.SetValue(newValue);
}

void DrillChapter19() {
	FirstLine("DrillChapter19()");
	cout << "Creating structure of type 'T', and testing...\n";

	//Drill #3
	DrillStructure<int> intStructure{4};
	DrillStructure<char> charStructure{'y'};
	DrillStructure<double> doubleStructure{10.25};
	DrillStructure<string> stringStructure{"My Structure"};
	DrillStructure<vector<int>> vectorStructure{vector<int>{10, 11, 12, 13, 14, 15}};


	//Drill #4, and adapted for Drill #7 & 8
	cout << "\nThe 'intStructure' variable content is: " << Get(intStructure) << '\n';
	cout << "The 'charStructure' variable content is: " << Get(charStructure) << '\n';
	cout << "The 'doubleStructure' variable content is: " << Get(doubleStructure) << '\n';
	cout << "The 'stringStructure' variable content is: " << Get(stringStructure) << '\n';

	cout << "The 'vectorStructure' variable content is: " << '\n';
	for (int i = 0; i < Get(vectorStructure).size(); ++i)
		cout << "\tvectorStructure[" << i << "]: " << Get(vectorStructure)[i] << '\n';


	//Drill #5, and then adapted for Drill #7 & 8
	cout << "\n*Testing external function 'Get()':\n";
	int& valueReference1 = Get(intStructure);
	cout << "The value of the 'DrillStructure' mValue property obtained from"
	        " a reference to this property is: " << valueReference1 << '\n';

	cout << "\nAssigning '15' using the 'reference' to DrillStructure.mValue\n";

	valueReference1 = 15;
	cout << "The new value of the 'DrillStructure' mValue property obtained from"
	        " a reference to this property is: " << Get(intStructure) << '\n';

	//Drill #6, and then adapted for Drill #7 & 8
	cout << "\n*Testing external function 'T& Get(DrillStructure<T>& drillStructure)':\n";
	double& valueReference2 = Get(doubleStructure);
	cout << "The value of the 'DrillStructure' mValue property obtained from"
	        " a reference to this property is: " << valueReference2 << '\n';

	cout << "\nAssigning '12.75' using the 'reference' to DrillStructure.mValue\n";

	valueReference2 = 12.75;
	cout << "The new value of the 'DrillStructure' mValue property obtained from"
	        " a reference to this property is: " << Get(doubleStructure) << '\n';


	//Drill #59
	cout << "\n*Testing external function 'Set()':\n";

	cout << "The value of the 'DrillStructure' mValue property obtained from"
	        " Get() function is: " << Get(doubleStructure) << '\n';

	cout << "\nAssigning '22.375' using the 'reference' to Set() external function\n";

	Set(doubleStructure, 22.375);
	cout << "The new value of the 'DrillStructure' mValue property obtained from"
	        " Get() function is: " << Get(doubleStructure) << '\n';

	/*have not done anymore from here (Drill #9)*/


	LastLine();
}

/***********************************************/
/*Exercises*/
void ExerciseTemplate() {
	FirstLine("ExerciseTemplate()");
	cout << "\nBlaBla.\n";


	LastLine();
}

//Exercise 01
template<class T>
void FunctionExercise01(vector<T>& vector1, const vector<T> vector2) {
	if (vector1.size() != vector2.size()) {
		cout << "\nThe 2 vectors must be of the same size.\n";
		return;
	}

	for (int i = 0; i < vector1.size(); ++i) {
		vector1[i] += vector2[i];
	}
}

void Exercise01() {
	FirstLine("Exercise01()");
	cout << "Adding the element of a vector to the ones of another.\n";

	vector<int> vectorInt1{1, 2, 3, 4, 5};
	vector<int> vectorInt2{10, 20, 30, 40, 50};

	cout << "\n'The 2 vectors operation on elements are : \n";
	for (int i = 0; i < vectorInt1.size(); ++i) {
		cout << "\t(vector1[" << i << "] = " << vectorInt1[i] << ") += (vector2[" << i << "] = " << vectorInt2[i]
		     << ")\n";
	}

	//**Running function
	cout << "\nRunning 'FunctionExercise01(vector1, vector2)', adding 'vector2' elements to 'vector1'.";
	FunctionExercise01(vectorInt1, vectorInt2);


	cout << "\nNew elements value for 'vector1' are:\n";
	for (int i = 0; i < vectorInt1.size(); ++i) {
		cout << "\tElement[" << i << "] = " << vectorInt1[i] << '\n';
	}

	LastLine();
}

int main() {
	cout << "Hello, Chapter19!" << endl;

//	Example19_2_1();
//	Example19_2_2();
//	Example19_2_3();
	Example19_2_4(); //works only in debug, or with the previous method calls disabled (?!)
	Example19_3_1();
	Example19_3_4();
	Example19_3_5();
	Example19_3_7();
	DrillChapter19();
	Exercise01();

	return 0;
}

