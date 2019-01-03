/*
 * Created by Yves Gingras on 2018-12-12.
 */

#include <iostream>
#include "TryThis.h"

using namespace std;

Try1752::Try1752() {

	cout << "In 'Try1752'" << '\n';
	cout << "Constructing " << mName <<  "\n\n";
}

Try1752::~Try1752() {
	cout << "In 'Try1752'" << '\n';
	cout << "Destructing " << mName <<  "\n\n";

}

Try1752A::Try1752A() {
	cout << "In 'Try1752A'" << '\n';
	cout << "Constructing " << mName <<  "\n\n";

}

Try1752A::~Try1752A() {
	cout << "In 'Try1752A'" << '\n';
	cout << "Destructing " << mName <<  "\n\n";
}
