//============================================================================
// Authors     : Jackson Benfer, Daniel Kelly, Ross Castillo, Michael Ton, Alexa Chase
// Date 	   : 04.14.14
// Class       : COP 3502 (6776)
// Assignment  : Calculator Project
// Description : ...
//============================================================================

#include "Number.h"
#include "Constant.h"
#include "Integer.h"
#include "Root.h"


#include <iostream>

using namespace std;

int main() {

	int base = 2;
	Number* inside = new Integer(4);

	Number* root = new Root(inside, base);

	cout << root->getString() << endl;
	cout << root-> getDecimal() << endl;

	Number* answer = root->calculate();

	cout << answer->getString() << endl;
	cout << answer->getDecimal() << endl;

	return 0;
}
