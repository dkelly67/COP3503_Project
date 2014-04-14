//============================================================================
// Author      : Daniel Kelly
// Created on  : 04.12.14
// File        : Multiplication.cpp
// Description : This class will multiply number types together.
//============================================================================

#include "Multiplication.h"

/* Initialization Constructor
 * Initializes "Numbers" array, called "terms"
 */
Multiplication::Multiplication(Number** multiplication, int size) {
	this->numOfTerms = size;
	this->terms = new Number * [this->numOfTerms];
	terms = multiplication;
}

Multiplication::Multiplication(Number* num1, Number* num2) {
	this->numOfTerms = 2;
	terms = new Number*[2];
	terms[0] = num1;
	terms[1] = num2;
}

// Return array of Numbers being multiplied.
Number** Multiplication::getTerms() {
	return this->terms;
}

// Output pure multiplication of entries inside 'terms'
double Multiplication::getDecimal() {
	double ans = 1;
	for (int i = 0; i < this->numOfTerms; i++) {
		ans = ans*terms[i]->getDecimal();
	}
	return ans;
}

// Outputs the string of the multiplicative array
string Multiplication::getString() {
	string type;
	string num;
	string numberString;
	for (int i = 0; i < this->numOfTerms; i++) {
		num = this->terms[i]->getString();
		if (i == 0) {
			numberString = num;
		}
		else {
			numberString = numberString + " * " + num;
		}
	}
	return numberString;
}

bool Multiplication::equals(Number * number) {
	return false;
}

/* Calls calculate on each object type within terms, then multiplies the
 * Numbers together to provide symbolic calculation.
 */
Number* Multiplication::calculate() {

	Number* intTotal = new Integer(1);
	Number* total = NULL;
	Number* term = NULL;
	int product = 1;
	int numeratorProduct = 1;
	int denomProduct = 1;

	for (int i = 0; i < this->numOfTerms; i++) {

		term = this->terms[i];

		if (typeid(*term) == typeid(Integer)) {
			Integer * intNum = (Integer *)term;

			product *= intNum->getInteger();

			intTotal = new Integer(product);
		}

		if (typeid(*term) == typeid(Fraction)) {
			Fraction *fract = (Fraction *)term;
			Number *num = fract->getNumerator();
			Number *den = fract->getDenominator();

			if (typeid(*num) == typeid(*den) && typeid(Integer) == typeid(*num)) {
				numeratorProduct *= ((Integer *)num)->getInteger();

				denomProduct *= ((Integer *)den)->getInteger();
			}
		}

		if(typeid(*term) == typeid(Multiplication)){
			Multiplication* mult = (Multiplication*) term;

			Number** newTerms = new Number*[this->numOfTerms + mult->numOfTerms];

			for(int i = 0; i < numOfTerms; i++)
				newTerms[i] = terms[i];
			for(int i = numOfTerms; i < numOfTerms + mult->numOfTerms; i++)
				newTerms[i] = mult->getTerms()[i-numOfTerms];

			Multiplication* ans = new Multiplication(newTerms, numOfTerms + mult->numOfTerms);

			return ans->calculate();
		}
	}

	numeratorProduct = ((Integer *)intTotal)->getInteger()*numeratorProduct;
	total = new Fraction(new Integer(numeratorProduct), new Integer(denomProduct));

	return total->calculate();
}



int Multiplication::getSize(){
	return numOfTerms;
}



Multiplication :: ~Multiplication(){
}
