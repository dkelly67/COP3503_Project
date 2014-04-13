

#include <sstream>
#include <typeinfo>
#include <iostream>
#include "Fraction.h"
#include "Integer.h"
#include <vector>

using namespace std;

Fraction::Fraction(Number* num, Number* den){
	this->num = num;
	this->den = den;
}


Number* Fraction::calculate(){


	Integer* n = (Integer*) num;
	Integer* d = (Integer*) den;

	vector<int> nFactors = n->getFactors();

	vector<int> dFactors = d->getFactors();

	//TODO: Really hacky way of doing this


	for(int i = 0; i < nFactors.size(); i++){
		for(int j = 0; j < dFactors.size(); j++){
			if(nFactors[i] == dFactors[j]){
				nFactors[i] = 4;
				dFactors[j] = 4;
			}
		}

	}

	int numValue = 1;
	int denValue = 1;

	for(int i = 0; i < nFactors.size(); i++){
		if(nFactors[i] != 4)
		numValue *= nFactors[i];
	}


	for(int i = 0; i < dFactors.size(); i++){
		if(dFactors[i] != 4)
		denValue *= dFactors[i];
	}

	if(denValue != 1)
		return new Fraction(new Integer(numValue), new Integer(denValue));
	else return new Integer(numValue);
}



Number* Fraction::getNumerator(){
	return num;
}

Number* Fraction::getDenominator(){
	return den;
}


double Fraction::getDecimal(){
	return num->getDecimal() / den->getDecimal();
}


string Fraction::getString(){
	ostringstream stream;

	//TODO: Check if parenthesis are nessasary

	stream << "(" << num->getString() << ")" <<  "/" << "(" << den->getString() << ")";

	return stream.str();
}



Fraction::~Fraction(){
	delete num;
	delete den;
}
