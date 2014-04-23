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
			else if(terms[i]->equals(new Integer(-1)) && i == 0){
				stream << "-";
				continue;
			}
			else
				stream << terms[i]->getString();
			if(i < numOfTerms-1)
				stream << " * ";
		}
		return stream.str();
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


	for (int i = 0; i < this->numOfTerms; i++){
		if(typeid(*terms[i]) == typeid(Integer)){
			if(((Integer*)terms[i])->getInteger() == 0)
				return new Integer(0);
			if(((Integer*)terms[i])->getInteger() == 1){
				Number** newTerms = new Number*[numOfTerms-1];
				int k = 0;
				for(int j = 0; j < numOfTerms; j++){
					if(j != i){
						newTerms[k] = terms[j];
						k++;
					}
				}
				terms = newTerms;
				numOfTerms--;
				i--;
				continue;
			}

		}



		for (int j = i + 1; j < this->numOfTerms; j++){

			//Integers

			if ((typeid(*this->terms[i]) == typeid(Integer)) && (typeid(*this->terms[j]) == typeid(Integer)))
			{
				Number* product = new Integer(((Integer*)terms[i])->getInteger() * ((Integer*)terms[j])->getInteger());
				return recursiveStep(product, i, j);
			}

			//Fractions

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

			if(terms[i]->equals(terms[j])){
				Number* product = new Exponent(terms[i], new Integer(2));
				return recursiveStep(product, i, j);
			}


			//Exponent

			if(typeid(*terms[i]) == typeid(Exponent) || typeid(*terms[j]) == typeid(Exponent)){

				//If the bases are the same add the powers

				Exponent* e1;
				Exponent* e2;

				if(typeid(*terms[i]) != typeid(Exponent))
					e1 = new Exponent(terms[i], new Integer(1));
				else
					e1 = (Exponent*)terms[i];
				if(typeid(*terms[j]) != typeid(Exponent))
					e2 = new Exponent(terms[j], new Integer(1));
				else
					e2 = (Exponent*)terms[j];

				if(e1->getInside()->equals(e2->getInside())){
					Number* s = new Summation(e1->getPower(), e2->getPower());
					Number* product = new Exponent(e1->getInside(), s);
					return recursiveStep(product, i, j);
				}
			}

			//Summation

			if(typeid(*terms[i]) == typeid(Summation) || typeid(*terms[j]) == typeid(Summation)){
				//Distributive Property


				Number** terms1;
				Number** terms2;
				int size1, size2;

				if(typeid(*terms[i]) != typeid(Summation)){
					terms1 = &terms[i];
					size1 = 1;
				}
				else{
					terms1 = ((Summation*)terms[i])->getTerms();
					size1 =  ((Summation*)terms[i])->getSize();
				}
				if(typeid(*terms[j]) != typeid(Summation)){
					terms2 = &terms[j];
					size2 = 1;
				}
				else{
					terms2 = ((Summation*)terms[j])->getTerms();
					size2 =  ((Summation*)terms[j])->getSize();
				}
				Summation* result = new Summation(new Integer(0), new Integer(0));
				for(int k = 0; k < size1; k++){
					for(int l = 0; l < size2; l++){
						Multiplication* m = new Multiplication(terms1[k], terms2[l]);
						result = new Summation(result, m);
					}
				}
				return recursiveStep(result, i, j);
			}
		}
	}

	//Find the int part (if it exists) and make it first


	for(int i = 0; i < numOfTerms; i++){

		if(typeid(*terms[i]) == typeid(Integer)){
			if(i != 0){

				Number* temp = terms[0];
				terms[0] = terms[i];
				terms[i] = temp;
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
	return ans->calculate();
}


int Multiplication::getSize(){
	return numOfTerms;
}


bool Multiplication::equals(Number * number) {

	if(number == NULL)
		return false;

	if(typeid(*number) != typeid(Multiplication))
		return false;


	Multiplication* m = (Multiplication*) number;

	if(numOfTerms != m->numOfTerms)
		return false;


	Number** terms1 = new Number*[numOfTerms];
	for(int a = 0; a < numOfTerms; a++)
		terms1[a] =  terms[a];

	Number** terms2 = new Number*[m->numOfTerms];
	for(int a = 0; a < m->numOfTerms; a++)
		terms2[a] =  m->terms[a];

	int counter = 0;

	for(int i = 0; i < numOfTerms; i++){
		for(int j = 0; j < m->numOfTerms; j++){
			if(terms1[i] != NULL && terms2[j] != NULL)
			if(terms1[i]->equals(terms2[j])){
				terms1[i] = NULL;
				terms2[j] = NULL;
				counter++;
				continue;
			}
		}
	}

	return counter == numOfTerms;
}


bool Multiplication::isLikeTerm(Multiplication* m){


	int a = 0;
	int b = 0;

	if(typeid(*terms[0]) == typeid(Integer))
		a = 1;

	if(typeid(*m->terms[0]) == typeid(Integer))
		b = 1;

	if(numOfTerms -a != m->numOfTerms - b)
			return false;

	Number** terms1 = new Number*[numOfTerms];
	for(int a = 0; a < numOfTerms; a++)
		terms1[a] =  terms[a];

	Number** terms2 = new Number*[m->numOfTerms];
	for(int a = 0; a < m->numOfTerms; a++)
		terms2[a] =  m->terms[a];

	int counter = 0;

	for(int i = a; i < numOfTerms; i++){
		for(int j = b; j < m->numOfTerms; j++){
			if(terms1[i] != NULL && terms2[j] != NULL)
			if(terms1[i]->equals(terms2[j])){
				terms1[i] = NULL;
				terms2[j] = NULL;
				counter++;
				continue;
			}
		}
	}

	return counter == numOfTerms - a;
}

int Multiplication::getIntComponent(){

	//Assume it has been calculated
	int i;
	if(typeid(*terms[0]) == typeid(Integer)){
		i = ((Integer*)terms[0])->getInteger();
	}
	else
		i = 1;
	return i;
}

Multiplication :: ~Multiplication(){
}










