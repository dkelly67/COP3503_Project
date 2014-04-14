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
	Number* fract = NULL;
	Number* intTotal = NULL;
	Number* fractTotal = NULL;
	Number* constAdd = NULL;
	Number* constCalc = NULL;
	Number* constTotal = NULL;
	Number* numerator1 = NULL;
	Number* numerator2 = NULL;
	Number* denominator1 = NULL;
	Number* denominator2 = NULL;

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
				add[0] = new Fraction(sum, new Integer(1)); //convert to fraction to allow addition with fractions
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

			if (typeid(*this->terms[i]) == typeid(*this->terms[j]) && typeid(*this->terms[i]) == typeid(Fraction))
			{
				numerator1 = ((Fraction*)terms[i])->getNumerator();
				numerator2 = ((Fraction*)terms[j])->getNumerator();
				denominator1 = ((Fraction*)terms[i])->getDenominator();
				denominator2 = ((Fraction*)terms[j])->getDenominator();
				Number* newNumer = new Integer(((Integer*)numerator1)->getInteger()*((Integer*)denominator2)->getInteger() + ((Integer*)numerator2)->getInteger()*((Integer*)denominator1)->getInteger());
				Number* newDenom = new Integer(((Integer*)denominator1)->getInteger()*((Integer*)denominator2)->getInteger());
				fract = new Fraction(newNumer, newDenom);
				Number** add = new Number*[numOfTerms - 1];
				add[0] = fract->calculate();
				int l = 1;
				for (int k = 0; k < this->numOfTerms; k++)
				{
					if (k != i && k != j)
					{
						add[l] = terms[k];
						l++;
					}
				}
				fractTotal = new Summation(add, numOfTerms - 1);
				return fractTotal->calculate();
			}

			if ((typeid(this->terms[i]) == typeid(this->terms[j])) && typeid(*this->terms[i]) == typeid(Constant))
			{
				Constant* c = (Constant *)terms[i];
				Number** mult = new Number*[2];
				mult[1] = c->calculate();
				int constCounter = 0;
				for (int k = 0; k < this->numOfTerms; k++)
				{
					if (terms[k]->calculate() == mult[1])
						constCounter++;
				}

				cout << constCounter << endl;
				mult[0] = new Integer(constCounter);
				constTotal = new Multiplication(mult, 2);
				return constTotal->calculate();
			}
		}
	}

	return this;
}

