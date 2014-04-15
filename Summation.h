//Daniel Kelly

#ifndef _SUMMATION_H
#define _SUMMATION_H

#include "Number.h"
#include <typeinfo>
#include <sstream>
#include <iostream>
#include <string>
#include "Integer.h"
#include "Fraction.h"
#include "Multiplication.h"
class Summation : public Number
{

public:

	//Constructor: Creates Multiplication object based on an array of Number objects
	Summation(Number **terms, int size);
	Summation(Number* num1, Number* num2);

	//Destructor
	~Summation();


	//Functions
	Number** getTerms(); //Returns the Number array being summed
	double getDecimal(); //Returns decimal form
	string getString(); //Returns string of summing terms
	Number* calculate(); //Iterates through the Number array, and performs calculate on their specific object types
	int getSize();
	bool equals(Number* number);
private: //data fields

	Number* recursiveStep(Number* sum, int i, int j);
	Number** terms; //Pointer to an array of Numbers, called terms
	int numOfTerms; //Number of terms in summmation
};

#endif //_SUMMATION_H_
