//============================================================================
// Created on  : 04.12.14
// File        : Logarithm.h
// Description : This class will represent the log function of a calculator.
//============================================================================

#ifndef LOGARITHM_H_
#define LOGARITHM_H_

#include "Number.h"

using namespace std;

class Logarithm : public Number {
public:
	// Initialization constructor
	Logarithm(Number* base, Number* arg);


	// Virtual functions from Number.h
	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();

	// Class functions
	Number* getBase();
	Number* getArg();

	bool equals(Number* number);

	// Destructor
	virtual ~Logarithm();

private:
	// Private variables
	Number* base;
	Number* arg;
};

#endif /* LOGARITHM_H_ */
