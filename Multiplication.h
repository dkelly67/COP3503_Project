//Daniel Kelly

#ifndef _MULTIPLICATION_H
#define _MULTIPLICATION_H

#include "Number.h"
#include "Integer.h"
#include <typeinfo>
#include <sstream>
#include <iostream>
#include <string>
#include "Fraction.h"
//#include <stdio>
class Multiplication : public Number
{

public:

	//Constructor: Creates Multiplication object based on an array of Number objects
	Multiplication(Number **terms, int size);

	//Destructor
	~Multiplication();


	//Functions
	Number** getTerms(); //Returns the Number array being multiplied
	double getDecimal(); //Returns decimal form
	string getString(); //Returns string of mulltiplying terms
	Number* calculate(); //Iterates through the Number array, and performs calculate on their specific object types
	bool equals(Number* number);
private: //data fields

	Number** terms; //Pointer to an array of Numbers, called terms
	int numOfTerms; //Number of terms in multiplicative array
};

#endif //_MULTIPLICATION_H_