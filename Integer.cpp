//============================================================================
// Created on  : 04.06.14
// File        : Integer.cpp
// Description : This class will represent all integers in our program.
//============================================================================

#include "Integer.h"

#include <sstream>
#include <iostream>
#include <typeinfo>

Integer::Integer(int i) {
	this->theInteger = i;
}

int Integer::getInteger() {
	return theInteger;
}

/* Creates an empty vector of pointers of type int called factors and then
 * passes that into the getFactors() method along with TheInteger to be
 * factored.
 */
vector<int> Integer::getFactors() {
	vector<int>* factors = new vector<int>();
	getFactors(theInteger, factors);
	return *factors;
}

/* This function breaks up TheInteger (passed in replacing x) into
 * all of its factors. A for-loop iterates from 2 to the value of half
 * of TheInteger while a nested if-statement is used for the factorization.
 * TheInteger is tested to see if it's divisible by two. If so, i and
 * TheInteger are factors and i must be prime so it is added to the vector
 * of factors. TheInteger may still not be prime and so the method is
 * recursively called again to keep factoring it down.
 */
void Integer::getFactors(int x, vector<int>* factors) {
	for (int i = 2; i <= x/2; i++) {
		if (x % i == 0) {
			factors->push_back(i);
			getFactors(x/i, factors);
			return;
		}
	}
	// If we get here, then x is prime and we are done
	factors->push_back(x);
}

/* Just as with Constant, there is no calculation to be involved regarding
 * an Integer unless an operator is used, so it just return itself.
 */
Number* Integer::calculate() {
	return this;
}

string Integer::getString() {
	ostringstream stream;
	stream << theInteger;
	return stream.str();
}

double Integer::getDecimal() {
	return theInteger;
}

bool Integer::equals(Number* number){
	if(typeid(*number) != typeid(Integer)) {
		return false;
	}
	Integer* i = (Integer*) number;
	return (this->getInteger() == i->getInteger());
}

Integer::~Integer() {
}
