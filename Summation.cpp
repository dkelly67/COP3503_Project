//Daniel Kelly

#include "Summation.h"

//Constructor, initializes "Numbers" array, called "terms"
Summation::Summation(Number ** summation, int size)
{
	this->numOfTerms = size;
	this->terms = new Number* [this->numOfTerms];
	terms = summation;
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
	string type;
	string num;
	string numberString;
	bool isZero = false;

	for (int i = 0; i < this->numOfTerms; i++)
	{
		
		num = this->terms[i]->getString();
		if (this->terms[i]->getString() == "0"){
			isZero = true;
			continue;
		}
		if (isZero)
			numberString = numberString + num;
		else
			numberString = num + " + " + numberString;
		isZero = false;
	}
	return numberString;
}

bool Summation::equals(Number* number)
{
	return false;
}
//Calls calculate on each object type within terms, then multiplies the Numbers together to provide symbolic calculation
Number* Summation::calculate()
{
	Number* sum = NULL;
	Number* intTotal;
	
	if (numOfTerms == 1)
		return this->terms[0];
	for (int i = 0; i < this->numOfTerms; i++)
	{

		for (int j = i + 1; j < this->numOfTerms; j++)
		{
			if (typeid(*this->terms[i]) == typeid(*this->terms[j]) &&  typeid(*this->terms[i]) == typeid(Integer))
			{
				sum = new Integer(((Integer*)terms[i])->getInteger() + ((Integer*)terms[j])->getInteger());
				Number** add = new Number*[numOfTerms - 1];
				add[0] = sum;
				int l = 1;
				for (int k = 0; k < this->numOfTerms; k++)
				{
					if (k != i && k != j){
						add[l] = terms[k];
						l++;
					}
				}
				intTotal = new Summation(add, numOfTerms - 1);
				return intTotal->calculate();
			}

			if (typeid(*this->terms[i]) == typeid(*this->terms[j]) && typeid(*this->terms[i]) == typeid(Integer))
			{

			}
		}
		
		

	}

	return this;
}

