//============================================================================
// Author      : Jackson Benfer
// Created on  : 04.06.14
// File        : Integer.h
// Description : This class will represent all integers in our program.
//============================================================================

#ifndef INTEGER_H_
#define INTEGER_H_
#include "Number.h"
#include <vector>
using namespace std;

class Integer : public Number {
public:
	// Initialization constructor
	Integer(int i);

	// Virtual functions from Number.h
	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();
	virtual bool equals(Number* number);

	// Class functions
	int getInteger();
	vector<int> getFactors();

	// Destructor
	virtual ~Integer();

private:
	// Private variable
	int theInteger;

	// Private function
	void getFactors(int x, vector<int>*);
};

#endif /* INTEGER_H_ */
