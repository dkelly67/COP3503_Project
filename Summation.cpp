//Daniel Kelly

#include "Summation.h"


//Constructor, initializes "Numbers" array, called "terms"
Summation :: Summation(Number *terms)
{
	int numOfTerms = size(terms);
	
	for (int i = 0; i < numOfTerms; i++)
	{
		this.terms[i] = terms[i];
	}
}

//Default destructor
Summation :: ~Summation(){}


//Return array of Numbers being added.
Number* Summation::getTerms()
{
	return this.terms;
}

//Output pure sum of entries inside 'terms'
double Summation::getDecimal()
{
	double ans = 0;
	for(int i = 0; i < this.numOfTerms; i++)
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
	for(int i  = 0; i < this.numOfTerms; i++)
	{
		type = typeid(this.terms[i]);
		
		switch(type)
		{
		case "Integer":
			num = Integer.getString();
			break;
		case "Exponent":
			num = Exponent.getString();
			break;
		case "Constant":
			num = Constant.getString();
			break;
		case "Fraction";
			num = Fraction.getString();
			break;
		case "Multiplication":
			num = Multiplication.getString();
			break;
		case "Summation":
			num = this.getString();
			break;
		case "Root":
			num = Root.getString();
			break;
		case "Logarithm":
			num = Logarithm.getString();
			break;
		default:
			num = "Nonexistent type id. Class doesn't exist. Check terms array or typeid of each class in project.";
			break;
		}
		if(i == 0)
			numbers = num;
		else
			numberString = strcat(numbers,"+",num);
			
	}	
	return numberString;	
}		
	
//Calls calculate on each object type within terms, then multiplies the Numbers together to provide symbolic calculation
Number Summation::calculate()
{
	string type;
	Number ans;
	Number 
	for (int i = 0; i < this.numOfTerms; i++)
	{
		type = typeid(this.terms[i]);
		
		switch(type)
		{
		case "Integer":
			ans = Integer.calculate();
			break;
		case "Exponent":
			ans = Exponent.calculate();
			break;
		case "Constant":
			ans = Constant.calculate();
			break;
		case "Fraction":
			ans = Fraction.calculate();
			break;
		case "Multiplication":
			ans = Multiplication.calculate();
			break;
		case "Summation":
			ans = this.calculate();
			break;
		case "Root":
			ans = Root.calculate();
			break;
		case "Logarithm":
			ans = Logarithm.calculate();
			break;
		default:
			ans = "Problem with calculate() function or class does not exist. Check terms and typeid.";
			break;
		}
		

		//IMPLEMENT WAY TO SYMBOLICALLY ADD VALUES.
		
	}
}

