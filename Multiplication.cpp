//Daniel Kelly


#include "Multiplication.h"

//Constructor, initializes "Numbers" array, called "terms"
Multiplication::Multiplication(Number* terms)
{
	int numOfTerms = sizeof(terms);

	for (int i = 0; i < numOfTerms; i++)
	{
		this->terms[i] = terms[i];
	}
}

//Default destructor
Multiplication :: ~Multiplication(){}


//Return array of Numbers being multiplied.
Number* Multiplication::getTerms()
{
	return this->terms;
}

//Output pure multiplication of entries inside 'terms'
double Multiplication::getDecimal()
{
	double ans = 1;
	for (int i = 0; i < this->numOfTerms; i++)
	{
		ans = ans*terms[i].getDecimal();
	}

	return ans;
}

//Outputs the string of the multiplicative array
string Multiplication::getString()
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
			numberString = numberString + " * " + num;

	}
	return numberString;
}

//Calls calculate on each object type within terms, then multiplies the Numbers together to provide symbolic calculation
Number* Multiplication::calculate()
{
	string type;
	Number* ans = NULL;
	for (int i = 0; i < this->numOfTerms; i++)
	{
		ans = this->terms[i].calculate();


		//IMPLEMENT WAY TO SYMBOLICALLY MULTIPLY VALUES.

	}

	return ans;
}

