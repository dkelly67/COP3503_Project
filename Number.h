//============================================================================
// Author      : Jackson Benfer
// Created on  : 04.06.14
// File        : Number.h
// Description : This class is abstract and contains virtual function's that
//				 each sub class will override for its respective purpose. In
//				 calculate(), Integer and Constant return themselves, while
//				 the rest call calculate() on interior Numbers before
//				 calculating itself.
//============================================================================

#ifndef NUMBER_H_
#define NUMBER_H_
#include <string>
using namespace std;

class Number {
public:
	// Constructor
	Number();

	// Virtual functions that will be overridden in all sub-classes
	// All set to zero because they are abstract and thus overridden
	virtual Number* calculate() = 0; // Returns a pointer of type Number of the simplified Number
	virtual string getString() = 0; // Returns a string representation of the simplified Number
	virtual double getDecimal() = 0; // Returns a double of Number, if requested from user
	virtual bool equals(Number* number) = 0; // Returns a bool to see if the two numbers are equal

	// Destructor
	virtual ~Number();
};

#endif /* NUMBER_H_ */
