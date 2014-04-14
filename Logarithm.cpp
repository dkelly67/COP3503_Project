//============================================================================
// Author      : Ross Castillo
// Created on  : 04.12.14
// File        : Logarithm.cpp
// Description : This class will represent the log function of a calculator.
//============================================================================

#include "Logarithm.h"
#include <sstream>
#include <math.h>
#include <typeinfo>
#include "Integer.h"
#include "Summation.h"
#include "Multiplication.h"
#include "Exponent.h"
#include "Root.h"

using namespace std;

Logarithm::Logarithm(Number* base, Number* arg) {
	this->base = base;
	this->arg = arg;
}

Number* Logarithm::getBase() {
	return base;
}

Number* Logarithm::getArg() {
	return arg;
}



Number* Logarithm::calculate() {


	if(base->equals(arg))
		return new Integer(1);


	if(typeid(arg) == typeid(Integer)){

		Integer* theInt = (Integer*) arg;


		vector<int> factors = theInt->getFactors();

		if(factors.size() > 1){
			Number** terms = new Number*[factors.size()];

			for(int i = 0; i < factors.size(); i++){
				terms[i] = new Logarithm(base, new Integer(factors[i]));
			}
			Summation* ans = new Summation(terms, factors.size());
			return ans->calculate();
		}
	}



	if(typeid(arg) == typeid(Multiplication)){
		Multiplication* mult = (Multiplication*)arg;

		if(mult->getSize() > 1){
			Number** logTerms;
			Number** terms = mult->getTerms();
			for(int i = 0; i < mult->getSize(); i++){
				terms[i] = new Logarithm(base, mult->getTerms()[i]);
			}
			Summation* ans = new Summation(terms, mult->getSize());
			return ans->calculate();

		}
	}

	if(typeid(arg) == typeid(Fraction)){
		Fraction* f = (Fraction*)arg;

		Multiplication* m = new Multiplication(new Integer(-1), f->getDenominator());

		Number** terms = new Number*[2];

		terms[0] = new Logarithm(base, f->getNumerator());
		terms[1] = new Logarithm(base, m);

		Summation* s = new Summation(terms, 2);

		return s->calculate();

	}

	if(typeid(arg) == typeid(Exponent)){

		Exponent* exp = (Exponent*)arg;

		if(base == exp->getInside())
			return exp->getPower();
		else{

		Multiplication* m = new Multiplication(exp->getPower(), exp->getInside());

		return m->calculate();
		}
		}

	if(typeid(*arg) == typeid(Root)){
		Root* root = (Root*)arg;

		Fraction* f = new Fraction(new Integer(1), new Integer(root->getRoot()));

		Multiplication* m = new Multiplication(f, new Logarithm(base, root->getInside()));

		return m->calculate();
	}



	return this;
}



string Logarithm::getString() {
	ostringstream stream;

	stream << "log_" << base << ":(" << arg << ")";

	return stream.str();
}



double Logarithm::getDecimal() {
	return log(arg->getDecimal()) / log(base->getDecimal());
}



bool Logarithm::equals(Number* number){
	if(typeid(number) != typeid(Logarithm))
		return false;

	Logarithm* l = (Logarithm*)number;

	return(base->equals(l->base) && arg->equals(l->arg));
}


Logarithm::~Logarithm() {
	delete base;
	delete arg;
}





