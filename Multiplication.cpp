//============================================================================
// Author      : Daniel Kelly
// Created on  : 04.12.14
// File        : Multiplication.cpp
// Description : This class will multiply number types together.
//============================================================================

#include "Multiplication.h"
#include "Constant.h"
#include "Integer.h"
#include "Root.h"

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
	ostringstream stream;

		for (int i = 0; i < this->numOfTerms; i++)
		{
			if(typeid(*terms[i]) != typeid(Integer) && typeid(*terms[i]) != typeid(Constant))
				stream << "(" << terms[i]->getString() << ")";
			else
				stream << terms[i]->getString();
			if(i < numOfTerms-1)
				stream << " * ";
		}
		return stream.str();
}

bool Multiplication::equals(Number * number) {
	return false;
}

/* Calls calculate on each object type within terms, then multiplies the
 * Numbers together to provide symbolic calculation.
 */
Number* Multiplication::calculate()
{
	//If one term

	if (numOfTerms == 1)
		return this->terms[0]->calculate();

	//Handle Multiplication within Multiplications

	for (int i = 0; i < this->numOfTerms; i++){

			if(typeid(*terms[i]) == typeid(*this)){

				Multiplication* s = (Multiplication*)(terms[i]);
				Number** someTerms = s->getTerms();
				int size = numOfTerms + s->getSize() -1;


				Number** newTerms = new Number*[size];
				int k = 0;

				for(int j = 0; j < numOfTerms; j++){
					if(j != i){
						newTerms[k] = terms[j];
						k++;
					}
				}
				for(int j = numOfTerms-1; j < size; j++)
					newTerms[j] = someTerms[j-numOfTerms+1];

				return (new Multiplication(newTerms, size))->calculate();
			}
		}


	//Calculate all terms

	for (int i = 0; i < this->numOfTerms; i++)
	{
		terms[i] = terms[i]->calculate();
	}


	for (int i = 0; i < this->numOfTerms; i++)
	{

		for (int j = i + 1; j < this->numOfTerms; j++)
		{
			if ((typeid(*this->terms[i]) == typeid(Integer)) && (typeid(*this->terms[j]) == typeid(Integer)))
			{
				Number* product = new Integer(((Integer*)terms[i])->getInteger() * ((Integer*)terms[j])->getInteger());
				return recursiveStep(product, i, j);
			}


			if (typeid(*this->terms[i]) == typeid(Fraction)|| typeid(*this->terms[j]) == typeid(Fraction))
			{
				Fraction* f1 = NULL;
				Fraction* f2 = NULL;

				if(typeid(*this->terms[i]) != typeid(Fraction))
					f1 = new Fraction(terms[i], new Integer(1));
				else
					f1 = (Fraction*)terms[i];

				if(typeid(*this->terms[j]) != typeid(Fraction))
					f2 = new Fraction(terms[j], new Integer(1));
				else
					f2 = (Fraction*)terms[j];

				Number* product = new Fraction(new Multiplication(f1->getNumerator(), f2->getNumerator()),
												new Multiplication(f1->getDenominator(), f2->getDenominator()));

				return recursiveStep(product, i, j);

			}

			//Root

			if(typeid(*terms[i]) == typeid(Root) && typeid(*terms[j]) == typeid(Root)){

				//If the roots are the same multiply the insides

				Root* r1 = (Root*) terms[i];
				Root* r2 = (Root*) terms[j];
				if(r1->getRoot() == r2->getRoot()){
					Number* m = new Multiplication(r1->getInside(), r2->getInside());
					Root* product = new Root(m, r1->getRoot());
					return recursiveStep(product, i, j);
				}
			}

			//Exponent

			//If the bases are the same add the powers

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
	return ans->calculate();
}


int Multiplication::getSize(){
	return numOfTerms;
}



Multiplication :: ~Multiplication(){
}
