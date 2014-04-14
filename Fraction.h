//============================================================================
// Author      : Jackson Benfer
// Created on  : 04.11.14
// File        : Constant.cpp
// Description : This class handles fractions of number types.
//============================================================================

#ifndef FRACTION_H_
#define FRACTION_H_
#include "Number.h"
#include "Integer.h"
using namespace std;

class Fraction : public Number{
public:

	// Initialization constructor
	Fraction(Number* num, Number* den);

	// Virtual functions from Number.h
	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();
	virtual bool equals(Number* number);

	// Class functions
	Number* getNumerator();
	Number* getDenominator();

	// Destructor
	virtual ~Fraction();

private:
	// Private Variables
	Number* num;
	Number* den;

	// Private function
	void reduceInts(Integer& n, Integer& d);
};

#endif /* FRACTION_H_ */
