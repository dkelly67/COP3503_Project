#ifndef _SUMMATION_H
#define _SUMMATION_H

#include "Number.h"
#include "Integer.h"
#include "Fraction.h"

#include <string>
#include <sstream>
#include <typeinfo>
#include <iostream>

using namespace std;

class Summation : public Number {

public:
	// Constructor: Creates Multiplication object based on an array of Number objects
	Summation(Number **terms, int size);

	// Virtual Functions from Number.h
	virtual Number** getTerms(); //Returns the Number array being summed
	virtual double getDecimal(); //Returns decimal form
	virtual string getString(); //Returns string of summing terms
	virtual Number* calculate(); //Iterates through the Number array, and performs calculate on their specific object types
	virtual bool equals(Number* number);

	// Class functions
	int getSize();
	bool equals(Number* number);

	// Destructor
	virtual ~Summation();

private:
	// Private Variables
	Number** terms; //Pointer to an array of Numbers, called terms
	int numOfTerms; //Number of terms in summation
};

#endif //_SUMMATION_H_
