//============================================================================
// Author      : Ross Castillo
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
	Logarithm(Number* base, Number* arg); // Initialization constructor
	virtual ~Logarithm(); // Destructor

	// Virtual functions from Number.h
	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();

	// Class functions
	Number* getBase();
	Number* getArg();

private:
	// Private variables
	Number* base;
	Number* arg;
};

#endif /* LOGARITHM_H_ */