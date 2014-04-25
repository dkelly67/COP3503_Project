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
		stream << terms[i]->getString();
		if(i < numOfTerms-1)
			stream << " + ";
	}
	return stream.str();
}


bool Summation::equals(Number* number)
{

	if(number == NULL)
		return false;

	if(typeid(*number) != typeid(Summation))
		return false;


	Summation* m = (Summation*) number;

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



Number* Summation::calculate()
{


	//If only one term

	if (numOfTerms == 1)
		return terms[0]->calculate();



	for (int i = 0; i < this->numOfTerms; i++){

		//Check for summations inside summations


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


		 //Remove zeros
		if(typeid(*terms[i]) == typeid(Integer)){
			if(((Integer*)terms[i])->getInteger() == 0){
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

			//Same term

			if(terms[i]->equals(terms[j])){

				Number* sum = new Multiplication(new Integer(2), terms[i]);
				return recursiveStep(sum, i, j);
			}


			if(typeid(*terms[i]) == typeid(Multiplication) || typeid(*terms[j]) == typeid(Multiplication)){


				Multiplication* m1 = NULL;
				Multiplication* m2 = NULL;

				if(typeid(*terms[i]) == typeid(Multiplication))
					m1 = (Multiplication*)terms[i];
				else
					m1 = new Multiplication(new Integer(1), terms[i]);

				if(typeid(*terms[j]) == typeid(Multiplication))
					m2 = (Multiplication*)terms[j];
				else
					m2 = new Multiplication(new Integer(1), terms[j]);


				if(m1->isLikeTerm(m2)){


					int c = m1->getIntComponent() + m2->getIntComponent();


					int a = 0;
					if(m1->getIntComponent() != 1)
						a = 1;

					Number** newTerms = new Number*[m1->getSize()-a+1];
					newTerms[0] = new Integer(c);


					for(int b = a; b < m1->getSize(); b++){
						newTerms[b-a+1] = m1->getTerms()[b];
					}

					Number* sum = new Multiplication(newTerms, m1->getSize()-a+1);

					return recursiveStep(sum, i, j);

				}
			}


			//TODO: Fractions


		}
	}




	//TODO: Simplify



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












