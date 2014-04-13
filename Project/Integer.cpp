/*
 * Integer.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Jackson
 */

#include "Integer.h"
#include <sstream>
#include <iostream>

using namespace std;


Integer::Integer(int i) {
	this->theInteger = i;

}


int Integer::getInteger(){
	return theInteger;
}

vector<int> Integer::getFactors(){

	vector<int>* factors = new vector<int>();

	getFactors(theInteger, factors);

	return *factors;
}


void Integer::getFactors(int theInt, vector<int>* factors){


	for(int i = 2; i <= theInt/2; i++){

		if(theInt % i == 0){

			//theInt divides evenly by 0, so i and theInt/i are factors

			//i must be prime, add it to the vector of factors

			factors->push_back(i);

			//theInt might still not be prime, keep factoring

			getFactors(theInt/i, factors);

			return;
		}
	}

	//If we get here than theInt is prime and we are done

	factors->push_back(theInt);

	}


Number* Integer::calculate(){
	return this;
}

string Integer::getString(){
	ostringstream stream;
	stream << theInteger;
	return stream.str();
}

double Integer::getDecimal(){
	return theInteger;
}



Integer::~Integer() {
}

