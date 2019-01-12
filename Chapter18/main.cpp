#include <iostream>
#include <vector>

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
/*Examples*/

//Initialization constructor.
void Example18_1() {
	class Vector {
	public:
		//basic constructor
		Vector(int size)
				: mSize{size},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		~Vector() {
			delete[] mElements;
		}

	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
	};

	//testing
	FirstLine("Example18_1()");
	cout << "Initializer-list constructor.\n";

	Vector vector1{1.1, 2.2, 3.3};
	cout << "\nContent of the 'initialized' Vector:\n";
	PrintDoubleArray(cout, vector1.mElements, vector1.mSize);

	LastLine();
}

//Copy Constructor.
void Example18_3_1() {
	class Vector18_3_1 {
	public:
		//basic constructor
		Vector18_3_1(int size)
				: mSize{size},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector18_3_1(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector18_3_1(const Vector18_3_1& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]} { //uninitialized memory for elements...
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		~Vector18_3_1() {
			delete[] mElements;
		}

	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
	};


	FirstLine("Example18_3_1()");
	cout << "Copy constructor.\n";

	Vector18_3_1 vector1{1.1, 2.2, 3.3};
	cout << "\nContent of the 'copied' Vector:\n";
	PrintDoubleArray(cout, vector1.mElements, vector1.mSize);

	cout << "\nContent of the vector2 being copied to:\n";
	Vector18_3_1 vector2 = vector1;
	PrintDoubleArray(cout, vector2.mElements, vector2.mSize);

	cout << "\nContent of the vector3 being copied to:\n";
	Vector18_3_1 vector3{vector1};
	PrintDoubleArray(cout, vector3.mElements, vector3.mSize);

	LastLine();
}

//Copy Assignment.
void Example18_3_2() {
	class Vector18_3_2 {
	public:
		//basic constructor
		Vector18_3_2(int size)
				: mSize{size},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector18_3_2(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector18_3_2(const Vector18_3_2& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]} { //uninitialized memory for elements...
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector18_3_2() {
			delete[] mElements;
		}

		//Copy Assignment
		Vector18_3_2& operator=(const Vector18_3_2& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;

			return *this;
		}

	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
	};


	FirstLine("Example18_3_2()");
	cout << "Copy assignment.\n";

	Vector18_3_2 vector1{1.1, 2.2, 3.3};
	cout << "\nContent of the 'assigned' Vector:\n";
	PrintDoubleArray(cout, vector1.mElements, vector1.mSize);

	cout << "\nContent of the vector2 being assigned to:\n";
	Vector18_3_2 vector2(3);
	vector2 = vector1;
	PrintDoubleArray(cout, vector2.mElements, vector2.mSize);

	cout << "\nContent of the vector3 being assigned to:\n";
	Vector18_3_2 vector3(3);
	vector3 = vector1;
	PrintDoubleArray(cout, vector3.mElements, vector3.mSize);

	LastLine();
}

// Access to 'const Vector elements
void Example18_5_1() {
	class Vector18_5_1 {
	public:
		//basic constructor
		Vector18_5_1(int size)
				: mSize{size},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector18_5_1(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector18_5_1(const Vector18_5_1& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]} { //uninitialized memory for elements...
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector18_5_1() {
			delete[] mElements;
		}

		//Copy Assignment
		Vector18_5_1& operator=(const Vector18_5_1& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;

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
	};

	FirstLine("Example18_5_1()");

	cout << "Subscript access of a 'const' vector.\n"
	     << "Using an overload 'const' 'operator[]()' method.";

	Vector18_5_1 vector1(10);
	for (int i = 0; i < vector1.mSize; ++i) {
		vector1[i] = i;
	}

	cout << '\n';
	PrintDoubleArray(cout, vector1.mElements, vector1.mSize);

	LastLine();
}

//Palindrome example using 'string'.
//->Set up; using 'sting'
bool IsPalidrome18_7_1(const string& passedString) {
	int first{0};
	int last = passedString.length() - 1;

	while (first < last) { // haven't reached the middle.
		if (passedString[first] != passedString[last])
			return false;

		++first; // move forward
		--last; // move backward
	}
	return true;
}

//->Set up; using 'array'
bool IsPalidrome18_7_2(const char passedString[], int charQty) {
	int first{0};
	int last = charQty - 1;

	while (first < last) { // haven't reached the middle.
		if (passedString[first] != passedString[last])
			return false;

		++first; // move forward
		--last; // move backward
	}
	return true;
}

//->Set up; using 'pointer'
bool IsPalidrome18_7_3(const char* first, char* last) {

	while (first < last) { // haven't reached the middle.
		if (*first != *last)
			return false;

		++first; // move forward
		--last; // move backward
	}
	return true;
}


void Example18_7_1() {
	FirstLine("Example18_7_1");
	cout << "Passing a std::string\n";

	//input samples
	/*
	    kayak
	    level
	    rotator
	    anna
	 */

	string testedString{"\nrotator"};

	cout << testedString << " is";
	if (!IsPalidrome18_7_1(testedString))
		cout << " not";

	cout << " a palindrome\n";

	LastLine();
}

void Example18_7_2() {
	FirstLine("Example18_7_2");
	cout << "Passing an array.\n";

	//input samples
	/*
	    kayak
	    level
	    rotator
	    anna
	 */

	string testedString{"\nrotator"};

	cout << testedString << " is";
	if (!IsPalidrome18_7_1(testedString))
		cout << " not";

	cout << " a palindrome\n";

	LastLine();
}

void Example18_7_3() {
	FirstLine("Example18_7_3");
	cout << "Passing pointers.\n";

	//input samples
	/*
	    kayak
	    level
	    rotator
	    anna
	 */

	string testedString{"\nrotator"};

	cout << testedString << " is";
	if (!IsPalidrome18_7_1(testedString))
		cout << " not";

	cout << " a palindrome\n";

	LastLine();
}

/***********************************************/
/*TryThis*/
//18_4_2 Set Up
struct SimpleTest {
	int mValue;

	//Default constructor
	SimpleTest() {
		Out("SimpleTest()", 0);
		mValue = 0;
	}

	// 1 argument constructor
	SimpleTest(int value) {
		mValue = value;
		Out("SimpleTest(int)", value);
	}

	//Copy constructor
	SimpleTest(const SimpleTest& copiedSimpleTest) {
		mValue = copiedSimpleTest.mValue;
		Out("SimpleTest(copiedSimpleTest)", copiedSimpleTest.mValue);
	}

	//Copy assignment
	SimpleTest& operator=(const SimpleTest& copiedSimpleTest) {
		Out("SimpleTest::operator=()", copiedSimpleTest.mValue);
		mValue = copiedSimpleTest.mValue;
		return *this;
	}

	//Destructor
	~SimpleTest() {
		Out("~SimpleTest()", 0);
//		cout << "\nb";
	}

	void Out(const string& methodSignature, int passedValue) {
		cout << this << "->" << methodSignature << ":" << mValue << "(" << passedValue << ")\n";
	}
};

SimpleTest Global(2);

SimpleTest Copy(SimpleTest a) {
	return a;
}

SimpleTest Copy2(SimpleTest a) {
	SimpleTest aa = a;
	return aa;
}

SimpleTest& RefTo(SimpleTest& a) {
	return a;
}

SimpleTest* Make(int i) {
	SimpleTest a(i);
	return new SimpleTest(a);

}

struct SimpleTest2 {
	SimpleTest a;
	SimpleTest b;
};

//Debugging constructor and destructor
void TryThis18_4_2() {
	FirstLine("TryThis18_4_2");
	cout << "Debugging constructor and destructor\n";

	cout << "\nLocal variable\n";
	SimpleTest local{4};

	cout << "\nCopy construction\n";
	SimpleTest local2{local};

	cout << "\nCopy assignment\n";
	local = SimpleTest{5};

	cout << "\nCall by value and return [Copy1]\n";
	local2 = Copy(local);

	cout << "\nCall by value and return [Copy2]\n";
	local2 = Copy2(local);

	cout << "\nLocal variable\n";
	SimpleTest local3{6};

	cout << "\nCall by reference and return\n";
	SimpleTest& reference = RefTo(local);

	cout << "\n'Delete' Make(7) - [method 'Make()' returns a pointer]\n";
	delete Make(7);

	cout << "\n'Delete' Make(8) - [method 'Make()' returns a pointer]\n";
	delete Make(8);

	cout << "\nDefault value [creating a vector of elements of type 'SimpleTest'.\n";
	vector<SimpleTest> vector1(4);

	cout << "\nUninitialized local variable [of 'SimpleTest2'.\n";
	SimpleTest2 local4;

	cout << "\nA SimpleTest on the free store [SimpleTest*]\n";
	auto* simpleTestPointer = new SimpleTest{9};

	cout << "\nDelete the free store allocation of 'SimpleTest*'\n";
	delete simpleTestPointer;

	cout << "\nLeaving the 'CallingMethod' method.\n";

	//a copy of the console output used to 'manually' control the result with the IDE 'find' functionality.
	/*
	*TryThis18_4_2*
	Debugging constructor and destructor

	Local variable
	0x7ffee6cfa9b0->SimpleTest(int):4(4)

	copy construction
	0x7ffee6cfa9a8->SimpleTest(copiedSimpleTest):4(4)

	copy assignment
	0x7ffee6cfa9a0->SimpleTest(int):5(5)
	0x7ffee6cfa9b0->SimpleTest::operator=():4(5)
	0x7ffee6cfa9a0->~SimpleTest():5(0)

	call by value and return1
	0x7ffee6cfa990->SimpleTest(copiedSimpleTest):5(5)
	0x7ffee6cfa998->SimpleTest(copiedSimpleTest):5(5)
	0x7ffee6cfa9a8->SimpleTest::operator=():4(5)
	0x7ffee6cfa998->~SimpleTest():5(0)
	0x7ffee6cfa990->~SimpleTest():5(0)

	call by value and return2
	0x7ffee6cfa980->SimpleTest(copiedSimpleTest):5(5)
	0x7ffee6cfa988->SimpleTest(copiedSimpleTest):5(5)
	0x7ffee6cfa9a8->SimpleTest::operator=():5(5)
	0x7ffee6cfa988->~SimpleTest():5(0)
	0x7ffee6cfa980->~SimpleTest():5(0)

	Local variable
	0x7ffee6cfa978->SimpleTest(int):6(6)

	call by reference and return

	'delete' Make(7) - [method 'Make()' returns a pointer]
	0x7ffee6cfa848->SimpleTest(int):7(7)
	0x7fb687700020->SimpleTest(copiedSimpleTest):7(7)
	0x7ffee6cfa848->~SimpleTest():7(0)
	0x7fb687700020->~SimpleTest():7(0)

	'delete' Make(8) - [method 'Make()' returns a pointer]
	0x7ffee6cfa848->SimpleTest(int):8(8)
	0x7fb687500020->SimpleTest(copiedSimpleTest):8(8)
	0x7ffee6cfa848->~SimpleTest():8(0)
	0x7fb687500020->~SimpleTest():8(0)

	Default value [creating a vector of elements of type 'SimpleTest'.
	0x7fb687500020->SimpleTest():8(0)
	0x7fb687500024->SimpleTest():0(0)
	0x7fb687500028->SimpleTest():0(0)
	0x7fb68750002c->SimpleTest():0(0)

	Uninitialized local variable [of 'SimpleTest2'.
	0x7ffee6cfa950->SimpleTest():-1737250960(0)
	0x7ffee6cfa954->SimpleTest():32767(0)

	A SimpleTest on the free store [SimpleTest*]
	0x7fb687500000->SimpleTest(int):9(9)

	Delete the free store allocation of 'SimpleTest*'
	0x7fb687500000->~SimpleTest():9(0)

	Leaving the main method.
	0x7ffee6cfa954->~SimpleTest():0(0)
	0x7ffee6cfa950->~SimpleTest():0(0)
	0x7fb68750002c->~SimpleTest():0(0)
	0x7fb687500028->~SimpleTest():0(0)
	0x7fb687500024->~SimpleTest():0(0)
	0x7fb687500020->~SimpleTest():0(0)
	0x7ffee6cfa978->~SimpleTest():6(0)
	0x7ffee6cfa9a8->~SimpleTest():5(0)
	0x7ffee6cfa9b0->~SimpleTest():5(0)
	0x108f0b1b0->~SimpleTest():2(0)
    */

}

// Access to Vector elements - Returning a value)
void TryThis18_5a() {
	class Vector18_5 {
	public:
		//basic constructor
		Vector18_5(int size)
				: mSize{size},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector18_5(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector18_5(const Vector18_5& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]} { //uninitialized memory for elements...
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector18_5() {
			delete[] mElements;
		}

		//Copy Assignment
		Vector18_5& operator=(const Vector18_5& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;

			return *this;
		}

		//to access content through subscript annotation...
		double operator[](int n) {
			return mElements[n];
		}


	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
	};

	FirstLine("TryThis18_5a()");

	cout << "Adding the subscript annotation to get to elements.\n"
	     << "\n1st try. No result to print.\n"
	     << "Only observing the compiler's warning\n";

	Vector18_5 vector1(10);
	double returnedValue = vector1[2]; //ok,
//	vector1[3] = returnedValue; //Not assignable; 'vector1[3]' is a value


	LastLine();
}

// Access to Vector elements - Returning a pointer to the element's value)
void TryThis18_5b() {
	class Vector18_5b {
	public:
		//basic constructor
		Vector18_5b(int size)
				: mSize{size},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector18_5b(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector18_5b(const Vector18_5b& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]} { //uninitialized memory for elements...
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector18_5b() {
			delete[] mElements;
		}

		//Copy Assignment
		Vector18_5b& operator=(const Vector18_5b& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;

			return *this;
		}

		//to access content through subscript annotation...
		double* operator[](int n) {
			return &mElements[n];
		}


	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
	};

	FirstLine("TryThis18_5b()");

	cout << "2ne try. Works, but not good enough.\n"
	     << "Need to 'dereference' the returned pointer to use the value.\n";

	Vector18_5b vector1(10);
	for (int i = 0; i < vector1.mSize; ++i) {
		*vector1[i] = i;
	}

	cout << '\n';
	PrintDoubleArray(cout, vector1.mElements, vector1.mSize);

	LastLine();
}

// Access to Vector elements - Returning a reference to the element's value)
void TryThis18_5c() {
	class Vector18_5c {
	public:
		//basic constructor
		Vector18_5c(int size)
				: mSize{size},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			for (int i = 0; i < mSize; ++i)
				mElements[i] = 0; //...initializing now
		}

		//initializer-list constructor
		Vector18_5c(initializer_list<double> initializerList)
				: mSize{static_cast<int>(initializerList.size())},
				  mElements{new double[mSize]} { //uninitialized memory for elements...
			copy(initializerList.begin(), initializerList.end(), mElements); //...initializing now, using std::copy.
		}

		//copy constructor
		Vector18_5c(const Vector18_5c& copiedVector)
				: mSize{copiedVector.mSize},
				  mElements{new double[copiedVector.mSize]} { //uninitialized memory for elements...
			copy(copiedVector.mElements, copiedVector.mElements + mSize, mElements);
		}

		//Destructor
		~Vector18_5c() {
			delete[] mElements;
		}

		//Copy Assignment
		Vector18_5c& operator=(const Vector18_5c& assignedVector) {
			auto* assignedElements = new double[assignedVector.mSize]; //allocate new temporary memory space.
			copy(assignedVector.mElements, assignedVector.mElements + mSize, assignedElements);
			delete[] mElements; //deallocate 'this' mElements pointer.
			mElements = assignedElements; // new assignment to 'this' mElements pointer.
			mSize = assignedVector.mSize;

			return *this;
		}

		//to access content through subscript annotation...
		double& operator[](int n) {
			return mElements[n]; //returns reference
		}


	public: //should be PRIVATE, but let 'public' for now so its possible to print for testing.
		int mSize;
		double* mElements;
	};

	FirstLine("TryThis18_5c()");

	cout << "3rd try. Returning a reference\n"
	     << "The way to go.\n";

	Vector18_5c vector1(10);
	for (int i = 0; i < vector1.mSize; ++i) {
		vector1[i] = i;
	}

	cout << '\n';
	PrintDoubleArray(cout, vector1.mElements, vector1.mSize);

	LastLine();
}

/***********************************************/
/*Drill; array*/
int globalArray[]{1, 2, 4, 8, 16, 32, 64, 128, 264, 512};

void FunctionArray(int passedArray[], int elementsQty) {
	int localArray[10];

	for (int i = 0; i < elementsQty; ++i) {
		localArray[i] = passedArray[i];
	}

	cout << "\nThe content of 'globalArray' variable:\n";
	PrintIntArray(cout, globalArray, elementsQty);

	cout << "\nThe content of 'localArray' variable:\n";
	PrintIntArray(cout, localArray, elementsQty);

	int* intPointer = new int[elementsQty];
	for (int j = 0; j < elementsQty; ++j) {
		intPointer[j] = passedArray[j];
	}

	cout << "\nThe content of 'intPointer' variable:\n";
	PrintIntArray(cout, intPointer, elementsQty);

	delete[] intPointer;
}

void DrillArray() {
	FirstLine("DrillArray");

	cout << "\nFirst call of 'FunctionArray()' method";
	FunctionArray(globalArray, 10);

	int factorialValues[]{1, 2 * 1, 3 * 2 * 1, 4 * 3 * 2 * 1, 5 * 4 * 3 * 2 * 1, 6 * 5 * 4 * 3 * 2 * 1,
	                      7 * 6 * 5 * 4 * 3 * 2 * 1, 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1, 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1,
	                      10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1};

	cout << "\nSecond call of 'FunctionArray()' method";
	FunctionArray(factorialValues, 10);

	LastLine();
}

/*Drill; vector*/
vector<int> globalVector{1, 4, 6, 64, 128, 256, 512, 1024, 2048, 4096};

void FunctionVector(const vector<int>& passedVector) {

	cout << "\nThe content of 'globalVector' variable:\n";
	PrintIntVector(cout, globalVector);

	vector<int> localVector1{globalVector};
	cout << "\nThe content of 'localVector1' variable:\n";
	PrintIntVector(cout, localVector1);

	vector<int> localVector2{passedVector};
	cout << "\nThe content of 'localVector2' variable:\n";
	PrintIntVector(cout, localVector2);

}

void DrillVector() {
	FirstLine("DrillVector");

	cout << "\nFirst call of 'FunctionVector()' method";
	FunctionVector(globalVector);

	vector<int> factorialValues{1, 2 * 1, 3 * 2 * 1, 4 * 3 * 2 * 1, 5 * 4 * 3 * 2 * 1, 6 * 5 * 4 * 3 * 2 * 1,
	                            7 * 6 * 5 * 4 * 3 * 2 * 1, 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1,
	                            9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1, 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1};

	cout << "\nSecond call of 'FunctionVector()' method";
	FunctionVector(factorialValues);

	LastLine();
}

/***********************************************/
/*Exercises*/
//various definitions - Begin

//used in exercise 1
char* StringdUp(const char* cString) {
	char* localCString = new char{};
	int charCounter{};

	while (*(cString + charCounter) != '\0'){
		*(localCString + charCounter) = *(cString + charCounter);
		++charCounter;
	}

	return localCString;
}

//used in exercise 2
char* FindX(const char* cString, const char* x) {
	char* localX  = new char{0};
	int charCounter{};

	while (*(cString + charCounter) != '\0'){
		if (*(cString + charCounter) == *x) {
			*localX = *x;
			break;
		}
		++charCounter;
	}

	return localX;
}

//various definitions - End

void ExerciseTemplate() {
	FirstLine("Exrecise()");




	LastLine();
}

void Exercise1() {
	FirstLine("Exercise1()");

	char cString[] {"Testing copying C-string to new pointer from exercise 1 - Ok."};
	PrintCString(cout,StringdUp(cString));

	LastLine();
}

void Exercise2() {
	FirstLine("Exercise2()");

	char* charX {FindX("Test from Exercise 2", "E")};

	cout << "Searching for E in the c-style string 'Test from Exercise 2.\n"
	     << "Found: " << *charX << endl;

	delete charX;
	LastLine();
}

/***********************************************/
int main() {
	cout << "Hello, Chapter18!" << endl;

	/*Examples*/
	Example18_1();
	Example18_3_1();
	Example18_3_2();
	TryThis18_4_2();
	TryThis18_5a();
	TryThis18_5b();
	TryThis18_5c();
	Example18_5_1();
	Example18_7_1();
	Example18_7_2();
	Example18_7_3();
	DrillArray();
	DrillVector();

	Exercise1();
//	Exercise2(); // works fine in DEBUG mode only. Can't find the fix (?!)

	cout << '\n';

	return 0;
}























































