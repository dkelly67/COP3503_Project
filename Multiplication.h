//============================================================================
// Created on  : 04.12.14
// File        : Multiplication.cpp
// Description : This class multiplies Number types together.
//============================================================================

#ifndef _MULTIPLICATION_H
#define _MULTIPLICATION_H

#include "Number.h"
#include "Integer.h"
#include "Fraction.h"
#include "Summation.h"

#include <typeinfo>
#include <sstream>
#include <iostream>
#include <string>

class Multiplication : public Number {
public:
	// Creates Multiplication object based on an array of Number objects
	Multiplication(Number **terms, int size);
	Multiplication(Number* num1, Number* num2);

	// Virtual functions from Number.h
	double getDecimal(); // Returns decimal form
	virtual string getString(); // Returns string of multiplying terms
	virtual Number* calculate();
	// Iterates through Number array, and performs calculate on specific object types
	virtual bool equals(Number* number);

	// Class functions
	Number** getTerms(); // Returns the Number array being multiplied
	int getSize();

	// Destructor
	virtual ~Multiplication();

private:
	// Private Variables
	Number** terms; // Pointer to an array of Numbers, called terms
	int numOfTerms; // Number of terms in multiplicative array
	Number* recursiveStep(Number* product, int i, int j);
};

#endif //_MULTIPLICATION_H_
