//============================================================================
// Created on  : 04.06.14
// File        : Constant.h
// Description : This class will represent the two constants, pi and e.
//============================================================================

#ifndef CONSTANT_H_
#define CONSTANT_H_
#include "Number.h"
using namespace std;

class Constant : public Number {
public:
	// Initialization Constructor
	Constant(bool isPi, bool isE);

	// Virtual functions from Number.h
	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();
	virtual bool equals(Number* number);

	// Class functions
	bool IsPi();
	bool IsE();

	// Destructor
	virtual ~Constant();

private:
	// Private variables
	bool pi;
	bool e;
};

#endif /* CONSTANT_H_ */
