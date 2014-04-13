//Daniel Kelly

#include "Multiplication.h"


//Constructor, initializes "Numbers" array, called "terms"
Multiplication :: Multiplication(Number *terms)
{
	int numOfTerms = size(terms);
	
	for (int i = 0; i < numOfTerms; i++)
	{
		this.terms[i] = terms[i];
	}
}

//Default destructor
Multiplication :: ~Multiplication(){}


//Return array of Numbers being multiplied.
Number* Multiplication::getTerms()
{
	return this.terms;
}

//Output pure multiplication of entries inside 'terms'
double Multiplication::getDecimal()
{
	double ans = 1;
	for(int i = 0; i < this.numOfTerms; i++)
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
			num = this.getString();
			break; //How would it return?
		case "Summation":
			num = Summation.getString();
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
			numberString = strcat(numbers,"*",num);
			
	}	
	return numberString;	
}		
	
//Calls calculate on each object type within terms, then multiplies the Numbers together to provide symbolic calculation
Number Multiplication::calculate()
{
	string type;
	Number ans;
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
			ans = this.calculate();
			break;
		case "Summation":
			ans = Summation.calculate();
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
		
		//IMPLEMENT WAY TO SYMBOLICALLY MULTIPLY VALUES.
		
	}
}

