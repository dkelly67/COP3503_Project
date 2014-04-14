//============================================================================
// Author      : Jackson Benfer
// Created on  : 04.06.14
// File        : Constant.cpp
// Description : This class will represent the two constants, pi and e.
//============================================================================

#include "Constant.h"
#include <stdexcept>

/* Initialization constructor. Sets the values of pi and e to true and throws
 * an exception just in case a constant other than pi or e is detected.
 */
Constant::Constant(bool isPi, bool isE) {
	this->pi = isPi;
	this->e = isE;
	if (!pi && !e) {
		throw out_of_range("Constant must be either e or pi");
	}
}

bool Constant::IsPi() {
	return pi;
}

bool Constant::IsE() {
	return e;
}

/* No need for calculation of a constant for this assignment, so it just
 * returns itself.
 */
Number* Constant::calculate() {
	return this;
}

string Constant::getString() {
	if (pi == true) {
		return "pi";
	}
	else if (e == true) {
		return "e";
	}
	else {
		throw out_of_range("Constant must be either e or pi");
	}
}

double Constant::getDecimal() {
	if (pi == true) {
		return 3.14159265358979323846;
	}
	else if (e == true) {
		return 2.71828182845904523536;
	}
	else {
		throw out_of_range("Constant must be either e or pi");
	}
}

bool Constant::equals(Number* number){
	if (typeid(*number) != typeid(Constant)) {
		return false;
	}
	Constant* c = (Constant*) number;
	return ((this->pi == c->pi) && (this->e == c->e));
}

Constant::~Constant() {
}
