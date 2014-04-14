//============================================================================
// Created on  : 04.12.14
// File        : Root.h
// Description : This class will represent the square root function.
//============================================================================

#ifndef ROOT_H_
#define ROOT_H_
#include "Number.h"
using namespace std;

class Root : public Number {
public:
	// Initialization constructor
	Root(Number* inside, int root);

	// Virtual functions from Number.h
	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();
	virtual bool equals(Number* number);

	// Class functions
	Number* getInside();
	int getRoot();

	// Destructor
	virtual ~Root();

private:
	// Private variables
	Number* inside;
	int root;
};

#endif /* ROOT_H_ */
