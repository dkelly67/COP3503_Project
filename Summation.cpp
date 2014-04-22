//Daniel Kelly

#include "Summation.h"

#include "Constant.h"
#include "Integer.h"

class Constant;

//Constructor, initializes "Numbers" array, called "terms"
Summation::Summation(Number ** summation, int size)
{
	this->numOfTerms = size;
	this->terms = new Number* [this->numOfTerms];
	terms = summation;
}


Summation::Summation(Number* num1, Number* num2){
	this->numOfTerms = 2;
	terms = new Number*[2];
	terms[0] = num1;
	terms[1] = num2;
}
//Default destructor
Summation :: ~Summation(){}


//Return array of Numbers being added.
Number** Summation::getTerms()
{
	return this->terms;
}

int Summation::getSize()
{
	return this->numOfTerms;
}
//Output pure sum of entries inside 'terms'
double Summation::getDecimal()
{
	double ans = 0;

	for (int i = 0; i < this->numOfTerms; i++)
	{
		
		ans = ans + terms[i]->getDecimal();
	}

	return ans;
}

//Outputs the string of the summation array
string Summation::getString()
{
	ostringstream stream;

	for (int i = 0; i < this->numOfTerms; i++)
	{
		if(typeid(*terms[i]) != typeid(Integer) && typeid(*terms[i]) != typeid(Constant))
			stream << "(" << terms[i]->getString() << ")";
		else
			stream << terms[i]->getString();
		if(i < numOfTerms-1)
			stream << " + ";
	}
	return stream.str();
}


bool Summation::equals(Number* number)
{
	return false;
}



Number* Summation::calculate()
{
	//If only one term

	if (numOfTerms == 1)
		return terms[0]->calculate();

	//Check for summations inside summations

	for (int i = 0; i < this->numOfTerms; i++){

		if(typeid(*terms[i]) == typeid(*this)){

			Summation* s = (Summation*)(terms[i]);
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

			return (new Summation(newTerms, size))->calculate();
		}
	}


	//Calculate

	for (int i = 0; i < this->numOfTerms; i++)
		terms[i] = terms[i]->calculate();


	//Combine like terms recursively

	//Iterate through all possible pairs

	for (int i = 0; i < this->numOfTerms; i++){
		for (int j = i + 1; j < this->numOfTerms; j++){

			//Integers

			if (typeid(*terms[i]) == typeid(Integer) &&  typeid(*terms[j]) == typeid(Integer)){

				Number* sum = new Integer(((Integer*)terms[i])->getInteger() + ((Integer*)terms[j])->getInteger());
				return recursiveStep(sum, i, j);
			}


			//Integers and Fractions with Integer denominators and numerators

			if((typeid(*terms[i]) == typeid(Fraction) || typeid(*terms[i]) == typeid(Integer)) &&
			   (typeid(*terms[j]) == typeid(Fraction) || typeid(*terms[j]) == typeid(Integer))){

				bool ok = true;

				int num1, num2, den1, den2;

			/*
			 * If term is an int, turn into fraction
			 * If terms is a fraction, make sure that num and den are Integer,
			 * If so, extract num and den
			 * Otherwise, set ok to false
			 *
			 * Repeat for second term
			 *
			 * Add the fractions if ok
			 *
			 */


				//Fraction 1

				if(typeid(*terms[i]) == typeid(Integer)){
					num1 = ((Integer*)terms[i])->getInteger();
					den1 = 1;
				}
				else{
					Fraction* f1 = (Fraction*)terms[i];
					if(typeid(*f1->getNumerator()) == typeid(Integer)){
						num1 = ((Integer*)f1->getNumerator())->getInteger();
					}else{
						ok = false;
					}
					if(typeid(*f1->getDenominator()) == typeid(Integer)){
						den1 = ((Integer*)f1->getDenominator())->getInteger();
					}else{
						ok = false;
					}
				}


				//Fraction 2
				if(typeid(*terms[j]) == typeid(Integer)){
					num2 = ((Integer*)terms[j])->getInteger();
					den2 = 1;
				}
				else{
					Fraction* f2 = (Fraction*)terms[j];
					if(typeid(*f2->getNumerator()) == typeid(Integer)){
						num2 = ((Integer*)f2->getNumerator())->getInteger();
					}else{
						ok = false;
					}
					if(typeid(*f2->getDenominator()) == typeid(Integer)){
						den2 = ((Integer*)f2->getDenominator())->getInteger();
					}else{
						ok = false;
					}
				}

				//Add

				if(ok){
					Fraction* f = new Fraction(new Integer(num1*den2 + num2*den1), new Integer(den1*den2));
					return recursiveStep(f, i, j);
				}
			}
		}
	}
	return this;
}



Number* Summation::recursiveStep(Number* sum, int i, int j){

	Number** newTerms = new Number*[numOfTerms - 1];
	newTerms[0] = sum;
	int l = 1;
	for (int k = 0; k < this->numOfTerms; k++)
	{
		if (k != i && k != j){
			newTerms[l] = terms[k];
				l++;
		}
	}

	Summation* ans = new Summation(newTerms, numOfTerms - 1);
	return ans->calculate();
}












