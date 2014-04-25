/*
 * Constant.cpp
 *
 *  Created on: Apr 6, 2014
 *      Author: Jackson
 */

#include "Constant.h"

#include <stdexcept>

#include <typeinfo>

using namespace std;


//TODO: Is there a way to make this more readable? Enumerations in C++?

Constant::Constant(bool isPi, bool isE) {
	this->pi = isPi;
	this->e = isE;
	if(!pi == !e)
		throw out_of_range("Constant must be either e or pi");
}

bool Constant::IsE(){
	return e;
}

bool Constant::IsPi(){
	return pi;
}


Number* Constant::calculate(){
	return this;
}

string Constant::getString(){
	if(pi)
		return "pi";
	else if(e)
		return "e";
	else
		throw out_of_range("Constant must be either e or pi");
}

double Constant::getDecimal(){
	if(pi)
		return 3.14159265358979323846;
	else if(e)
		return 2.71828182845904523536;
	else
		throw out_of_range("Constant must be either e or pi");
}


bool Constant::equals(Number* number){

	if(number == NULL)
		return false;

	if(typeid(*number) != typeid(Constant))
		return false;

	Constant* c = (Constant*) number;

	return (this->pi == c->pi && this->e == c->e);
}

Constant::~Constant() {
}

