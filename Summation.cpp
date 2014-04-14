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
	for (int i = 0; i < this->numOfTerms; i++)
	{
		num = this->terms[i]->getString();
		if (i == 0)
			numberString = num;
		else
			numberString = numberString + " + " + num;
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
	Number* intTotal = new Integer(0);
	Number* total = NULL;
	Number* term = NULL;
	int sum = 0;
	int numeratorSum = 0;
	int denomSum = 1;

	for (int i = 0; i < this->numOfTerms; i++)
	{

		term = this->terms[i];

		if (typeid(*term) == typeid(Integer))
		{
			Integer * intNum = (Integer *)term;

			sum += intNum->getInteger();

			intTotal = new Integer(sum);
		}

		if (typeid(*term) == typeid(Fraction))
		{
			Fraction *fract = (Fraction *)term;
			Number *num = fract->getNumerator();
			Number *den = fract->getDenominator();
				
			if (typeid(*num) == typeid(*den) && typeid(Integer) == typeid(*num))
			{
				numeratorSum = numeratorSum*((Integer*)den)->getInteger() + ((Integer*)num)->getInteger()*denomSum;

				denomSum *= ((Integer *)den)->getInteger();
			}
			
		}

	}
	
	
		numeratorSum = ((Integer *)intTotal)->getInteger()*denomSum + numeratorSum;
		total = new Fraction(new Integer(numeratorSum), new Integer(denomSum));
	
	return total->calculate();
}

