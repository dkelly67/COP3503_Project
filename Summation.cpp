//Daniel Kelly

#include "Summation.h"


//Constructor, initializes "Numbers" array, called "terms"
Summation::Summation(Number *terms)
{
	int numOfTerms = sizeof(terms);

	for (int i = 0; i < numOfTerms; i++)
	{
		this->terms[i] = terms[i];
	}
}

//Default destructor
Summation :: ~Summation(){}


//Return array of Numbers being added.
Number* Summation::getTerms()
{
	return this->terms;
}

//Output pure sum of entries inside 'terms'
double Summation::getDecimal()
{
	double ans = 0;
	for (int i = 0; i < this->numOfTerms; i++)
	{
		ans = ans + terms[i].getDecimal();
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
		num = this->terms[i].getString();
		if (i == 0)
			numberString = num;
		else
			numberString = numberString + " + " + num;
	}
	return numberString;
}

//Calls calculate on each object type within terms, then multiplies the Numbers together to provide symbolic calculation
Number* Summation::calculate()
{
	string type;
	Number* ans = NULL;
	for (int i = 0; i < this->numOfTerms; i++)
	{
		ans = this->terms[i].calculate();


		//IMPLEMENT WAY TO SYMBOLICALLY ADD VALUES
	}

	return ans;
}

