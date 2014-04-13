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

/*bool equals(Number* number)
{
	if (typeid) == typeid(*number))
	{

	}
}*/
//Calls calculate on each object type within terms, then multiplies the Numbers together to provide symbolic calculation
Number* Summation::calculate()
{
	Number* total = NULL;
	Number* one = NULL;
	Number* two = NULL;
	int sum = 0;
	for (int i = 0; i < this->numOfTerms; i++)
	{

		one = this->terms[i];

		if (typeid(*one) == typeid(Integer))
		{
			Integer * intOne = (Integer *)one;

			sum += intOne->getInteger();

			total = new Integer(sum);
		}

		
		
	}

	return total;
}

