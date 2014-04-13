//Daniel Kelly

#ifndef _SUMMATION_H
#define _SUMMATION_H

#include "Number.h"
#include <typeinfo>
#include <sstream>
#include <string>
#include <stdio>

class Summation : public Number
{
	
	public:
	
		//Constructor: Creates Multiplication object based on an array of Number objects
		Summation(Number *terms);
		
		//Destructor
		~Summation();
		
		
		//Functions
		Number* getTerms(); //Returns the Number array being summed
		double getDecimal(); //Returns decimal form
		string getString(); //Returns string of summing terms
		Number calculate(); //Iterates through the Number array, and performs calculate on their specific object types
	
	private: //data fields
	
		Number terms[]; //Pointer to an array of Numbers, called terms
		
}

#endif //_SUMMATION_H_