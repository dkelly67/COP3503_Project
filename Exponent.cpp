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

using namespace std;

Exponent::Exponent(Number* inside, Number* power){
	this->inside = inside;
	this->power = power;
}

Number* Exponent::calculate(){


	inside = inside->calculate();
	power = power->calculate();

	if(typeid(*inside) == typeid(Integer) && typeid(*power) == typeid(Integer)){
		Number* ans = new Integer(this->getDecimal());
		delete this;
		return ans;
	}

	if(typeid(*power) == typeid(Integer)){
		Integer* p = (Integer*) power;
		if(p->getInteger() < 0){
			Fraction* f = new Fraction(new Integer(1), new Exponent(inside, new Integer(-p->getInteger())));
			delete this;
			return f->calculate();
		}
	}


	if(typeid(*power) == typeid(Fraction)){
		Fraction* f = (Fraction*)power;

		//return a root

	}




	return this;
}

double Exponent::getDecimal(){

	//TODO: non int powers


	if(power->getDecimal() == 0)
		return 1;

	double ans = 1;

	for(int i = 0; i < power->getDecimal(); i++){
		ans *= inside->getDecimal();
	}

	return ans;

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


