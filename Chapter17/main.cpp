#include <iostream>
#include <vector>
#include "TryThis.h"
#include "Link.h"

using namespace std;

/*Utility*/
void FirstLine(const string& name) {
	cout << "\n*" << name << "*" << endl;
}

void LastLine() {
	cout << "----------------------------------\n";
}

/*Examples*/
/**
 * @brief Link struct, used in example from 17_9_3
 */
struct Link {
	string mValue;
	Link* mPredecessor;
	Link* mSuccessor;

	Link(const string& value, Link* prev = nullptr, Link* succ = nullptr)
			: mValue{value}, mPredecessor{prev}, mSuccessor{succ} { /*...*/ }
};

//List operations used with Link struct- Begin
/**
 * @brief Insert a new Link* 'before' the passed 'currentLink'. Used in 17_9_3b
 */
Link* Insert(Link* currentLink, Link* newLink) {
	if (newLink == nullptr)
		return currentLink;

	if (currentLink == nullptr)
		return newLink;

	newLink->mSuccessor = currentLink; //newLink is placed 'before' currentLink.

	if (currentLink->mPredecessor) //if currentLink has a predecessor Link...
		currentLink->mPredecessor->mSuccessor = newLink; //...its Successor becomes newLink (instead of currentLink)

	newLink->mPredecessor = currentLink->mPredecessor; // currentLink Predecessor becomes newLink Predecessor.
	currentLink->mPredecessor = newLink; // newLink become currentLink Predecessor.


	return newLink;
}

/**
 * @brief Add a new Link* 'after' the passed 'currentLink'.
 */
Link* Add(Link* currentLink, Link* newLink) {
	if (newLink == nullptr)
		return currentLink;

	if (currentLink == nullptr)
		return newLink;

	newLink->mPredecessor = currentLink; //newLink is placed 'after' currentLink.

	if (currentLink->mSuccessor) //if currentLink has a successor Link...
		currentLink->mSuccessor->mPredecessor = newLink; //...its Predecessor becomes newLink (instead of currentLink)

	newLink->mSuccessor = currentLink->mSuccessor; // currentLink Successor becomes newLink Successor.
	currentLink->mSuccessor = newLink; // newLink become currentLink Successor.


	return newLink;
}

/**
 * @brief Remove 'currentPointer' from list (of Links)
 * @param currentPointer
 * @return Returns 'currentPointer' successor.
 */
Link* Erase(Link* currentPointer) {
	if (currentPointer == nullptr)
		return nullptr;

	// and pointers fiddling...
	if (currentPointer->mSuccessor) // if currentPointer has a successor...
		currentPointer->mSuccessor->mPredecessor = currentPointer->mPredecessor; /* .. its predecessor becomes
                                                                                  * currentPointer predecessor.s*/

	if (currentPointer->mPredecessor)
		currentPointer->mPredecessor->mSuccessor = currentPointer->mSuccessor;

	return currentPointer->mSuccessor;


}

/**
 * @brief Find currentPointer's value in Link list.
 * @param currentPointer
 * @param value The current pointer's value.
 * @return Returns the found Link pointer or nullptr.
 */
Link* Find(Link* currentPointer, const string& value) {
	while (currentPointer) {
		if (currentPointer->mValue == value)
			return currentPointer;

		currentPointer = currentPointer->mSuccessor;
	}

	return nullptr;
}

/**
 * @brief Move 'step' position in list of Links
 *
 * Positive 'step' moves forward, negative moves backward.
 * @param currentPointer
 * @param step The number of moves in either direction.
 * @return Pointer found at 'step' position if != nullptr, 'nullptr' otherwise.
 */
Link* Advance(Link* currentPointer, int step) {
	if (currentPointer == nullptr)
		return nullptr;


	if (0 < step) { /*moves forward.*/
		while (step--) {
			if (currentPointer->mSuccessor == nullptr)
				return nullptr;

			currentPointer = currentPointer->mSuccessor;
		}
	} else if (step < 0) { /*negatives steps*/
		while (step++) {
			if (currentPointer->mPredecessor == nullptr)
				return nullptr;

			currentPointer = currentPointer->mPredecessor;
		}
	}

	return currentPointer;
}

void PrintAll(Link* linkedList) {
	cout << "{ ";
	while (linkedList) {
		cout << linkedList->mValue << flush;
		if (linkedList->mSuccessor != nullptr)
			cout << ", ";

		linkedList = linkedList->mSuccessor;
	}
	cout << " }";
}
//List operations used with Link struct- End

/*Drill (generic functions definitions) - begin*/
void PrintIntArray(ostream& outStream, int* a, int qtyElements) {
	for (int i = 0; i < qtyElements; ++i)
		outStream << "array[" << to_string(i) << "] = " << a[i] << endl;
}

void PrintVector(ostream& outStream, vector<int>* a) {
	for (auto i = 0; i < a->size(); ++i)
		outStream << "array[" << i << "] = " << (*a)[i] << endl;
}

int* InitializeArray(int qtyElements, int firstValue) {
	int* myArray = new int[qtyElements];
	for (int i = 0; i < qtyElements; ++i) {
		myArray[i] = firstValue + i;
	}

	return myArray;
}

vector<int>* InitializeVector(int qtyElements, int firstValue) {
	auto* myVector = new vector<int>(static_cast<unsigned long>(qtyElements));

	for (int i = 0; i < qtyElements; ++i) {
		(*myVector)[i] = firstValue + i;
	}

	return myVector;
}
/*Drill (definitions) - end*/

/*Exercises related; various functions definitions - Begin*/
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

/**
 * @brief Related to Exercise 3.
 * @param cString
 */
void ToLower(char* cString) {
	for (int i = 0; cString[i] != '\0'; ++i) {
		int charInt{cString[i]};
		if (charInt > 64 && charInt < 91) {
			cString[i] = charInt + 32;
		}
	}
}

char* StringdUp(const char* cString) {
	char* myCString = new char{};

	int charCounter{};
	for (int j = 0; cString[j] != '\0'; ++j) {
		charCounter++;
	}
	charCounter++; // Includes the final '\0'.

	for (int i = 0; i < charCounter; ++i)
		myCString[i] = cString[i];

	return myCString;
}

char* FindX(const char* cString, const char* x) {
	char* myX = new char{'0'};

	for (int i = 0; cString[i] != '\0'; ++i) {
		if (cString[i] == *x) {
			*myX = *x;
			break;
		}
	}

	return myX;
}

void PrintCharArray(ostream& outStream, char* a, int qtyElements) {
	for (int i = 0; i < qtyElements; ++i)
		outStream << "array[" << to_string(i) << "] = " << a[i] << endl;
}

void GetPrintableInput(istream& instream) {
	cout << "Enter printable input: " << endl;

	vector<char> inputCharacters{};
	char input{};
//	int charCounter{};
	while (instream >> input) {
		if (input == '!')
			return;

//		charCounter++;
		inputCharacters.push_back(input);


	}


}

// Various function calls related to exercice 9.
void Call2();
void Call3();
void Call4();
void Call5();

void Call1() {
	int* intPointer1 = new  int{1};
	int* intPointer2 = new  int{2};
	int* intPointer3 = new  int{3};
	int* intPointer4 = new  int{4};
	int* intPointer5 = new  int{5};

	Call2();
	delete intPointer1;
	delete intPointer2;
	delete intPointer3;
	delete intPointer4;
	delete intPointer5;
}

void Call2() {
	int* intPointer21 = new  int{21};
	int* intPointer22 = new  int{22};
	int* intPointer23 = new  int{23};
	int* intPointer24 = new  int{24};
	int* intPointer25 = new  int{25};

	Call3();
	delete intPointer21;
	delete intPointer22;
	delete intPointer23;
	delete intPointer24;
	delete intPointer25;
}

void Call3() {
	int* intPointer31 = new  int{31};
	int* intPointer32 = new  int{32};
	int* intPointer33 = new  int{33};
	int* intPointer34 = new  int{34};
	int* intPointer35 = new  int{35};

	Call4();
	delete intPointer31;
	delete intPointer32;
	delete intPointer33;
	delete intPointer34;
	delete intPointer35;
}

void Call4() {
	int* intPointer41 = new  int{41};
	int* intPointer42 = new  int{42};
	int* intPointer43 = new  int{43};
	int* intPointer44 = new  int{44};
	int* intPointer45 = new  int{45};

	Call5();
	delete intPointer41;
	delete intPointer42;
	delete intPointer43;
	delete intPointer44;
	delete intPointer45;
}

void Call5() {
	int* intPointer51 = new  int{51};
	int* intPointer52 = new  int{52};
	int* intPointer53 = new  int{53};
	int* intPointer54 = new  int{54};
	int* intPointer55 = new  int{55};

	cout << " "; // use a breakpoint here(!), to monitor stack behavior and free store memory assigned addresses order.

	delete intPointer51;
	delete intPointer52;
	delete intPointer53;
	delete intPointer54;
	delete intPointer55;
	//
}
/*Exercises related; various functions definitions - End*/

//*********************************************************

/**
 * @brief Demonstration of 'sizeof()'
 */
void Example17_3_1() {
	FirstLine("Example17_3_1()");

	char character{'z'};
	int intValue{5000};
	int* intPointer{&intValue};
	cout << "The size in bytes of a 'char' type is " << sizeof(char) << ", and of a defined 'char' value is "
	     << sizeof(character) << '\n';
	cout << "The size in bytes of an 'int' type is " << sizeof(int) << ", and of a defined 'int' value is "
	     << sizeof(intValue) << '\n';
	cout << "The size in bytes of a 'pointer  to an int' is " << sizeof(int*)
	     << ", and of a defined 'int pointer' value is " << sizeof(intPointer) << '\n';

	LastLine();
}

/**
 * @brief Range: Pointer does not know how many objects it points to.
 */
void Example17_4_3() {
	FirstLine("Example17_4_3()");

	auto* p = new double;
	auto* q = new double[1000];

	q[700] = 7.7; //fine
	cout << "The value of 'q[700]' is: " << to_string(q[700]) << '\n';
	q = p; //let q (first memory case) point to the same as p (first memory case).
	double d = q[700]; //out range access; no compiler warning!
	cout << "The value of 'd' is: " << to_string(d) << '\n';


	LastLine();
}

void Example17_5() {
	FirstLine("Example17_5()");

	class vector17_5 {
	public:
		explicit vector17_5(int s)
				: mSz{s}, mElem{new double[s]} {
			/*...*/
		}

		~vector17_5() {
			delete[] mElem;
		}

		int size() const {
			return mSz;
		}

		double get(int n) {
			return mElem[n];
		}

		void set(int n, double v) {
			mElem[n] = v;
		}

	private:
		int mSz;
		double* mElem;
	};

	//usage
	vector17_5 v(5);
	for (int i = 0; i < v.size(); ++i) {
		v.set(i, 1.1 * i);
		cout << "v[" << i << "]==" << v.get(i) << '\n';
	}

	LastLine();

}

/**
 * @brief First iteration of the 'Link*' exaple
 */
void Example17_9_3a() {
	FirstLine("Example17_9_3a()");

	Link* norseGods = new Link{"Thor"};

	norseGods = new Link{"Odin", nullptr,
	                     norseGods}; //new Link pointer, defining its 'mSuccessor' as the current Link pointer,
	norseGods->mSuccessor->mPredecessor = norseGods; /*'Odin' is  now the current Link pointer, so defining itself
                                          * as as being the 'previous' Link pointer of its own
                                          * 'successor' Link pointer. */

	norseGods = new Link{"Freia", nullptr, norseGods}; /*sane as previous Link pointer addition...*/
	norseGods->mSuccessor->mPredecessor = norseGods; /*sane as previous update to current 'successor' Link pointer. */

	LastLine();


}

/**
 * @brief Addition of the 'Link* Insert(Link* previous, Link* new)
 */
void Example17_9_3b() {
	FirstLine("Example17_9_3b()");

	Link* norseGods = new Link{"Thor"};
	norseGods = Insert(norseGods, new Link{"Odin"});
	norseGods = Insert(norseGods, new Link{"Freia"});

	LastLine();
}

/**
 * @brief Building 2 list, and correcting the wrond input.
 */
void Example17_9_5() {
	FirstLine("Example17_9_5()");

	Link* norseGods = new Link{"Thor"};
	norseGods = Insert(norseGods, new Link{"Odin"});
	norseGods = Insert(norseGods, new Link{"Zeus"});
	norseGods = Insert(norseGods, new Link{"Freia"});

	Link* greekGods = new Link{"Hera"};
	greekGods = Insert(greekGods, new Link{"Athena"});
	greekGods = Insert(greekGods, new Link{"Mars"});
	greekGods = Insert(greekGods, new Link{"Poseidon"});

	PrintAll(norseGods);
	cout << '\n';

	PrintAll(greekGods);
	cout << '\n';

	// Correcting the input
	Link* linkPointer = Find(greekGods, "Mars");
	if (linkPointer)
		linkPointer->mValue = "Ares";

	linkPointer = Find(norseGods, "Zeus");
	if (linkPointer) {
		if (linkPointer == norseGods)
			norseGods = linkPointer->mSuccessor;

		Link* test = Erase(linkPointer);
		greekGods = Insert(greekGods, linkPointer);
	}

	cout << "\nAnd after having corrected the input: \n";
	PrintAll(norseGods);
	cout << '\n';

	PrintAll(greekGods);
	cout << '\n';

	LastLine();
}

void Example17_10_1() {
	FirstLine("Example17_10_1()");

	Gods::Link* norseGods = new Gods::Link{"Thor"};
	norseGods = norseGods->Insert(new Gods::Link{"Odin"});
	norseGods = norseGods->Insert(new Gods::Link{"Zeus"});
	norseGods = norseGods->Insert(new Gods::Link{"Freia"});

	Gods::Link* greekGods = new Gods::Link{"Hera"};
	greekGods = greekGods->Insert(new Gods::Link{"Athena"});
	greekGods = greekGods->Insert(new Gods::Link{"Mars"});
	greekGods = greekGods->Insert(new Gods::Link{"Poseidon"});

	Gods::PrintAll(norseGods);
	cout << '\n';

	Gods::PrintAll(greekGods);
	cout << '\n';

	// Correcting the input
	Gods::Link* linkPointer = greekGods->Find("Mars");
	if (linkPointer)
		linkPointer->mValue = "Ares";

	linkPointer = norseGods->Find("Zeus");
	if (linkPointer) {
		if (linkPointer == norseGods)
			norseGods = linkPointer->Next();

		Gods::Link* testReturn = linkPointer->Erase();
		greekGods = greekGods->Insert(linkPointer);;
	}

	cout << "\nAnd after having corrected the input: \n";
	PrintAll(norseGods);
	cout << '\n';

	PrintAll(greekGods);
	cout << '\n';

	LastLine();
}

/*TryThis*/
/**
 * @brief sizeof() a vector with 20 elements.
 */
void TryThis17_3_1() {
	FirstLine("TryThis17_3_1()");

	vector<int> vector1(1000);
	cout << "The size  in bytes of 'vector<int> (1000)' is: " << sizeof(vector1) << '\n';
	cout << "The count of elements in 'vector<int> (1000)' is: " << vector1.size() << '\n';

	LastLine();
}

void TryThis17_5_2() {
	FirstLine("TryThis17_5_2()");

	cout << "Instantiating 'Try1752'" << '\n';
	Try1752 try1752;

	cout << "Instantiating 'Try1752A'" << '\n';
	Try1752A try1752A;


	cout << "Leaving the current call.\n\n";
//LastLine();


}

/*Drill - Part1*/
void Drill1_1To1_3() {
	FirstLine("Drill1_1To1_3()");

	int* myArray = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for (int i = 0; i < 10; ++i)
		cout << "myArray[" << to_string(i) << "] = " << myArray[i] << endl;

	delete[] myArray;

	LastLine();
}

/*Drill - Part2*/
void Drill2_13() {
	FirstLine("Drill2_13()");

	auto* p1 = new vector<int>{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
	vector<int>* p2 = new vector<int>(10, 0);

	cout << "Same as 'Drill2_10' to 'Drill2_12', but using vectors." << endl;

	cout << "\nThe content of vector 'p1':" << endl;
	PrintVector(cout, p1);

	cout << "\nThe content of vector 'p2':" << endl;
	PrintVector(cout, p2);

	p2 = p1;
	cout << "\nAssignation 'p2 = p1'"
	     << "\nThe content of vector 'p1':" << endl;
	PrintVector(cout, p1);

	cout << "\nThe content of vector 'p2':" << endl;
	PrintVector(cout, p2);

	delete p1;

	LastLine();
}

void Drill1_4() {
	FirstLine("Drill1_4()");

	int qtyElements{10};
	int* myArray = InitializeArray(qtyElements, 1);
	PrintIntArray(cout, myArray, qtyElements);

	delete[] myArray;

	LastLine();
}

void Drill1_5() {
	FirstLine("Drill1_5()");

	int qtyElements{10};
	int* myArray = InitializeArray(qtyElements, 100);
	PrintIntArray(cout, myArray, qtyElements);

	delete[] myArray;

	LastLine();
}

void Drill1_6() {
	FirstLine("Drill1_6()");

	int qtyElements{11};
	int* myArray = InitializeArray(qtyElements, 100);
	PrintIntArray(cout, myArray, qtyElements);

	delete[] myArray;

	LastLine();
}

void Drill1_8() {
	FirstLine("Drill1_8()");

	int qtyElements{20};
	int* myArray = InitializeArray(qtyElements, 100);
	PrintIntArray(cout, myArray, qtyElements);

	delete[] myArray;

	LastLine();
}

void Drill1_10() {
	FirstLine("Drill1_10()");

	vector<int>* drill5 = InitializeVector(10, 100);
	cout << "Equivalent to Drill1_5() but using a vector:" << endl;
	PrintVector(cout, drill5);

	vector<int>* drill6 = InitializeVector(11, 100);
	cout << "\nEquivalent to Drill1_6() but using a vector:" << endl;
	PrintVector(cout, drill6);

	vector<int>* drill8 = InitializeVector(20, 100);
	cout << "\nEquivalent to Drill1_8() but using a vector:" << endl;
	PrintVector(cout, drill8);

	delete drill5;
	delete drill6;
	delete drill8;

	LastLine();
}

//Global variables used in the 2nd part of the Drill.
int* p1 = new int{7};

int* p2 = new int[7]{2, 4, 6, 8, 10, 12, 14};

void Drill2_1To2() {
	FirstLine("Drill2_1To2()");

	cout << "The 'p1' pointer specifications: \n"
	     << "Address: \t\t\t\t" << p1
	     << "\nValue it points to: \t" << *p1 << endl;

	//global variable p1 & p2 are deleted by the last method using them

	LastLine();
}

void Drill2_3To4() {
	FirstLine("Drill2_3To4()");

	cout << "The 'p2' pointer specifications: \n"
	     << "Array address is: " << p2
	     << "\nArray content is: " << endl;

	PrintIntArray(cout, p2, 7);

	//global variable p1 & p2 are deleted by the last method using them

	LastLine();
}

void Drill2_5To9() {
	FirstLine("Drill2_5To9()");

	cout << "p1 address is: " << p1
	     << "\np2 address is: " << p2 << endl;


	int* p3 = p2;
	cout << "\nAssignation 'p3 = p2'"
	     << "\np1 address is: " << p1
	     << "\np2 address is: " << p2
	     << "\np3 address is: " << p3 << endl;


	p2 = p1;
	cout << "\nAssignation 'p2 = p1'"
	     << "\np1 address is: " << p1
	     << "\np2 address is: " << p2
	     << "\np3 address is: " << p3 << endl;

	p3 = p2;
	cout << "\nAssignation 'p3 = p2'"
	     << "\np1 address is: " << p1
	     << "\np2 address is: " << p2
	     << "\np3 address is: " << p3 << endl;

	cout << "\nThe value of p1 is: " << *p1
	     << "\nThe value of p2 is: " << *p2 << endl;

	delete p1;

	LastLine();
}

void Drill2_10To12() {
	FirstLine("Drill2_10To12()");

	int* p1 = new int[10]{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
	int* p2 = new int[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	cout << "The content of array 'p1':" << endl;
	PrintIntArray(cout, p1, 10);

	cout << "\nThe content of array 'p2':" << endl;
	PrintIntArray(cout, p2, 10);

	p2 = p1;
	cout << "\nAssignation 'p2 = p1'"
	     << "\nThe content of array 'p1':" << endl;
	PrintIntArray(cout, p1, 10);

	cout << "\nThe content of array 'p2':" << endl;
	PrintIntArray(cout, p2, 10);

	delete[] p1;

	LastLine();
}

/*Exercises*/
void Exercise_Template() {
	FirstLine("Exercise_()");




	LastLine();
}

void Exercise_3() {
	FirstLine("Exercise_3()");

	cout << "ThIs WhOLe SeNtEnCE WaS OrigNAlLy MiXTe WItH UpPer aND LOweR CHaRActERs." << endl;
	char myCString[]{"ThIs WhOLe SeNtEnCE WaS OrigNAlLy MiXTe WItH UpPer aND LOweR CHaRActERs."};

	ToLower(myCString);
	PrintCString(cout, myCString);

	LastLine();
}

void Exercise_4() {
	FirstLine("Exercise_4()");

	const char* cString1{"Testing copying C-string to new pointer from exercise 4 - Ok."};
	char* cString2{StringdUp(cString1)};

	PrintCString(cout, cString2);

	delete cString2;
	LastLine();
}

void Exercise_5() {
	FirstLine("Exercise_5()");

	char* charX = FindX("Test from Exercise 5", "E");

	cout << "Searching for E in the c-style string 'Test from Exercise 5.\n"
	     << "Found: " << *charX << endl;

	delete charX;
	LastLine();
}

void Exercise_6() {
	FirstLine("Exercise_6()");

	int counter{};
	while (true) {
		counter++;
		int* number = new int{};

		cout << counter << "," << flush;
	}


	LastLine();
}

void Exercise_7() {

	FirstLine("Exercise_7()");

	char* ArrayChars = new char[1000];
	char input{};
	int charsCounter{};

	cout << "Enter printable input: " << endl;
	while (cin >> input) {
		if (input == '!') { // input completed.
			if (ArrayChars[0] == ' '){
				cout << "No printable input received.\n"
				     << "Program terminated."<< endl;
				return;
			}
			else {
				cout << "\nThe content of the array of 'char' is:\n";
				PrintCharArray(cout,ArrayChars,charsCounter);
				cout << "Done!" << endl;
				break;
			}
		}
		ArrayChars[charsCounter] = input;
		charsCounter++;
	}

	delete[] ArrayChars;

	LastLine();
}

void Exercise_7b() {
	FirstLine("Exercise_7b()");
	cout << "Using a vector to temporarily store the input characters.\n";

	char input{};
	vector<char> vectorCharacters{};
	char* arrayChars = new char[vectorCharacters.size()];

	cout << "Enter printable input: " << endl;
	while (cin >> input) {
		if (input == '!') { // input completed.
			if (vectorCharacters.empty()){
				cout << "No printable input received.\n"
					 << "Program terminated."<< endl;
				return;
			}
			else {
				for (int i = 0; i < vectorCharacters.size(); ++i)
					arrayChars[i] = vectorCharacters[i];

				cout << "\nThe content of the array of 'char' is:\n";
				PrintCharArray(cout, arrayChars, static_cast<int>(vectorCharacters.size()));
				cout << "Done!" << endl;

				break;
			}
		}
		vectorCharacters.push_back(input);
	}

	delete[] arrayChars;

	LastLine();
}

void Exercise_8() {
	FirstLine("Exercise_8()");

	char input{};
	string stringChars{};

	cout << "Enter printable input: " << endl;
	while (cin >> input) {
		if (input == '!') { // input completed.
			if (stringChars.empty()){
				cout << "No printable input received.\n"
				     << "Program terminated."<< endl;
				return;
			}
			else {
				cout << "\nThe content of 'string' created is:\n";
				for (const auto& stringChar : stringChars)
					cout << stringChar;

				break;
			}
		}
		stringChars += input;
	}

	cout << "\nDone!";
	LastLine();
}

void Exercise_9() {
	FirstLine("Exercise_9()");
	cout << "Use debugger 'breakpoint' to monitor stack behavior and\n"
		    "free store memory assigned addresses order." << endl;

	Call1();

	LastLine();
}

void Exercise_13() {
	FirstLine("Exercise_13()");

	Gods::Link* norseGods = new Gods::Link{"Thor"};
	norseGods = norseGods->Insert(new Gods::Link{"Odin"});
	norseGods = norseGods->Insert(new Gods::Link{"Fulla"});
	norseGods = norseGods->Insert(new Gods::Link{"Nanna"});
	norseGods = norseGods->Insert(new Gods::Link{"Vidar"});

	Gods::Link* greekGods = new Gods::Link{"Zeus"};
	greekGods = greekGods->Insert(new Gods::Link{"Poseidon"});
	greekGods = greekGods->Insert(new Gods::Link{"Hera"});
	greekGods = greekGods->Insert(new Gods::Link{"Hades"});
	greekGods = greekGods->Insert(new Gods::Link{"Dionysus"});

	cout << "\n**nNorse Gods**\n";
	Gods::PrintAll2(norseGods);

	cout << "\n**Greek Gods**\n";
	Gods::PrintAll2(greekGods);

	//todo To be completed from "Add a member function 'add_ordered()'"...

	LastLine();
}

int main() {
	cout << "Hello, Chapter17!" << endl;

	/*Examples*/
	Example17_3_1();
	Example17_4_3();
	Example17_5();
	Example17_9_3a();
	Example17_9_3b();
	Example17_9_5();
	Example17_10_1();

	/*TryThis*/
	TryThis17_3_1();
	TryThis17_5_2();

	/*Drill*/
	Drill1_1To1_3();
	Drill1_4();
	Drill1_5();
	Drill1_6();
	Drill1_8();
	Drill2_1To2();
	Drill2_3To4();
	Drill2_5To9();
	Drill2_10To12();
	Drill1_10();
	Drill2_13();

	/*Exercises*/
	Exercise_3();
	Exercise_4();
	Exercise_5();
//	Exercise_6(); //endless loop for testing memory exhaustion.
//	Exercise_7(); // requires input
//	Exercise_7b(); // requires input
//	Exercise_8(); // requires input
//	Exercise_9(); // unresolved, not all the time error, related with 'released' memory objects being accessed.
	Exercise_13();

	return 0;
}