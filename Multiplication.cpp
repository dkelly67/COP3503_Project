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
Number* Multiplication::calculate()
{

	//Works with ints
	for (int i = 0; i < this->numOfTerms; i++)
	{
		terms[i] = terms[i]->calculate();
	}


	if (numOfTerms == 1)
		return this->terms[0];
	for (int i = 0; i < this->numOfTerms; i++)
	{

		for (int j = i + 1; j < this->numOfTerms; j++)
		{
			if ((typeid(*this->terms[i]) == typeid(Integer)) && (typeid(*this->terms[j]) == typeid(Integer)))
			{
				Number* product = new Integer(((Integer*)terms[i])->getInteger() * ((Integer*)terms[j])->getInteger());
				return recursiveStep(product, i, j);
			}




			if ((typeid(*this->terms[i]) == typeid(Integer)) || (typeid(*this->terms[i]) == typeid(Fraction)))
			if ((typeid(*this->terms[j]) == typeid(Integer)) || (typeid(*this->terms[j]) == typeid(Fraction)))
			{
				Fraction* f1 = NULL;
				Fraction* f2 = NULL;

				if(typeid(*this->terms[i]) == typeid(Integer))
					f1 = new Fraction(terms[i], new Integer(1));
				else
					f1 = (Fraction*)terms[i];

				if(typeid(*this->terms[j]) == typeid(Integer))
					f2 = new Fraction(terms[j], new Integer(1));
				else
					f2 = (Fraction*)terms[j];

				Number* product = new Fraction(new Multiplication(f1->getNumerator(), f2->getNumerator()),
												new Multiplication(f1->getDenominator(), f2->getDenominator()));

				return recursiveStep(product, i, j);

			}

			if (typeid(*this->terms[i]) == typeid(*this->terms[j]) && typeid(*this->terms[i]) == typeid(Integer))
			{

			}
		}



	}

	return this;
}


Number* Multiplication::recursiveStep(Number* product, int i, int j){

	Number** newTerms = new Number*[numOfTerms - 1];
	newTerms[0] = product;
	int l = 1;
	for (int k = 0; k < this->numOfTerms; k++)
	{
		if (k != i && k != j){
			newTerms[l] = terms[k];
				l++;
		}
	}

	Multiplication* ans = new Multiplication(newTerms, numOfTerms - 1);
	//ans->calculate()->getString();
	return ans->calculate();
}




Number* Multiplication::calculate1() {

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


		if(typeid(*term) == typeid(Summation)){
			Summation* s = (Summation*)term;
			Number** numbers = new Number*[s->getSize()];
			Number** otherTerms = new Number*[numOfTerms];
			int j = 0;
			for(int i = 0; i < numOfTerms; i++){
				if(terms[i] != s){
					otherTerms[j] = terms[i];
					j++;
				}
			}
			Multiplication* multOtherTerms = new Multiplication(otherTerms, numOfTerms-1);
			for(int i = 0; i < s->getSize(); i++){
				numbers[i] = new Multiplication(s->getTerms()[i], multOtherTerms);
			}

			Summation* theSum = new Summation(numbers, s->getSize());
			return theSum->calculate();
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
