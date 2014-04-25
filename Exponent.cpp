/*
 * Exponent.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: Jackson
 */

#include "Exponent.h"
#include <sstream>
#include <typeinfo>
#include "Integer.h"
#include "Fraction.h"
#include "Constant.h"
#include <iostream>
#include "Multiplication.h"
#include "Root.h"
#include "Summation.h"
#include <math.h>

using namespace std;

Exponent::Exponent(Number* inside, Number* power){
	this->inside = inside;
	this->power = power;
}

Number* Exponent::calculate(){


	inside = inside->calculate();
	power = power->calculate();

	if(typeid(*inside) == typeid(Integer) && typeid(*power) == typeid(Integer)){
		if(power->getDecimal() > 0){
		Number* ans = new Integer(this->getDecimal());
		return ans;
		}
		else{
			Fraction* f = new Fraction(new Integer(1), this);
			return new Fraction(new Integer(1), new Integer(f->getDecimal()));
		}
	}

	if(power->getDecimal() < 0){
		Fraction* f = new Fraction(new Integer(1), new Exponent(inside, new Multiplication(new Integer(-1), power)));
		return f->calculate();
	}

	if(typeid(*power) == typeid(Integer)){


		Integer* pow = (Integer*) power;
		int p = pow->getInteger();


		if(p == 0){
			delete this;
			return new Integer(1);
		}
		if(p == 1)
			return inside;



		if(typeid(*inside) == typeid(Fraction)){

			Fraction* f = (Fraction*)inside;

			Number* num = new Exponent(f->getNumerator(), new Integer(p));
			Number* den = new Exponent(f->getDenominator(), new Integer(p));

			Fraction* frac = new Fraction(num, den);

			return frac->calculate();

		}


	}


	if(typeid(*power) == typeid(Fraction)){
		Fraction* f = (Fraction*)power;
		Integer* i = (Integer*)f->getDenominator();

		Exponent* exp = new Exponent(inside, f->getNumerator());
		Root* root = new Root(exp, i->getInteger());

		return root->calculate();

	}

	if(typeid(*inside) == typeid(Exponent)){
		Exponent* exp = (Exponent*)inside;
		Number** terms = new Number*[2];
		terms[0] = power;
		terms[1] = exp->power;
		Multiplication* mult = new Multiplication(terms, 2);

		Exponent* ans = new Exponent(exp->inside, mult);

		return ans->calculate();
	}

	if(typeid(*inside) == typeid(Root)){
		Root* root = (Root*)inside;

		Exponent* exp = new Exponent(root->getInside(), power);

		Root* ans = new Root(exp, root->getRoot());

		return ans->calculate();
	}

	if(typeid(*inside) == typeid(Multiplication)){
		Multiplication* mult = (Multiplication*)inside;

		Number** multTerms = mult->getTerms();
		Number** terms = new Number*[mult->getSize()];

		for(int i = 0; i < mult->getSize(); i++){
			terms[i] = new Exponent(multTerms[i], power);
		}

		Number* ans = new Multiplication(terms, mult->getSize());

		return ans->calculate();

	}

	if(typeid(*inside) == typeid(Summation) && typeid(*power) == typeid(Integer)){
		int p = ((Integer*)power)->getInteger();
		Number** terms = new Number*[p];

		for(int i = 0; i < p; i++){
			terms[i] = inside;
		}

		Multiplication* ans = new Multiplication(terms, p);
		return ans->calculate();
	}


	return this;
}

double Exponent::getDecimal(){

	return pow(inside->getDecimal(), power->getDecimal());

}

string Exponent::getString(){
	ostringstream stream;


	if(typeid(*inside) != typeid(Integer) && typeid(*inside) != typeid(Constant)){
		stream << "(";
	}

	stream << inside->getString();

	if(typeid(*inside) != typeid(Integer) && typeid(*inside) != typeid(Constant)){
		stream << ")";
	}

	stream << "^";

	if(typeid(*power) != typeid(Integer) && typeid(*power) != typeid(Constant)){
			stream << "(";
		}

	stream << power->getString();

	if(typeid(*power) != typeid(Integer) && typeid(*power) != typeid(Constant)){
			stream << ")";
		}


	return stream.str();

}
bool Exponent::equals(Number* number){


	if(number == NULL)
		return false;


	if(typeid(*number) != typeid(Exponent))
		return false;

	Exponent* e = (Exponent*)number;

	Number* in1 = this->inside;
	Number* in2 = e->inside;
	Number* power1 = this->power;
	Number* power2 = e->power;

	return in1->equals(in2) && power1->equals(power2);

}

Number* Exponent::getInside(){
	return inside;
}

Number* Exponent::getPower(){
	return power;
}

Exponent::~Exponent(){
	delete inside;
	delete power;
}


