

#include <sstream>
#include <typeinfo>
#include <iostream>
#include "Fraction.h"
#include "Integer.h"
#include "Constant.h"
#include <vector>
#include "Multiplication.h"
#include "Root.h"
#include "Exponent.h"
#include "Summation.h"
#include "Logarithm.h"

using namespace std;

Fraction::Fraction(Number* num, Number* den){
	this->num = num;
	this->den = den;
}


Number* Fraction::calculate(){


	num = num->calculate();
	den = den->calculate();


	// 0

	if(typeid(*num) == typeid(Integer))
		if(((Integer*)num)->getInteger() == 0)
			return new Integer(0);

	//1

	if(num->equals(den))
		return new Integer(1);


	//Try to reduce


	if(reduceNumbers(&num, &den)){
		return calculate();
	}


	//Root

	if(typeid(*den) == typeid(Root)){

		cout << "Here" << endl;
		Root* r = (Root*)den;

		num = new Multiplication(num, new Exponent(r, new Integer(r->getRoot()-1)));
		den = r->getInside();

		cout << num->getString() << endl;

		return calculate();
	}

	//Conjugate

	if(typeid(*den) == typeid(Summation)){
		Summation* s = (Summation*)den;
		if(s->getSize() == 2){
			Number** terms = s->getTerms();
			Number* root = NULL;
			Number* nonRoot = NULL;

			if(typeid(*terms[0]) == typeid(Root)){
				root = new Multiplication(terms[0], new Integer(-1));
				nonRoot = terms[1];
			}

			if(typeid(*terms[1]) == typeid(Root)){
				root = new Multiplication(terms[1], new Integer(-1));
				nonRoot = terms[0];
			}

			if(typeid(*terms[0]) == typeid(Multiplication)){
				Multiplication* mult = (Multiplication*) terms[0];
				for(int i = 0; i < mult->getSize(); i++)
					if(typeid(*mult->getTerms()[i]) == typeid(Root)){
						root = new Multiplication(mult, new Integer(-1));
						nonRoot = terms[1];
					}
			}

			if(typeid(*terms[1]) == typeid(Multiplication)){
				Multiplication* mult = (Multiplication*) terms[1];
				for(int i = 0; i < mult->getSize(); i++)
					if(typeid(*mult->getTerms()[i]) == typeid(Root)){
						root = new Multiplication(mult, new Integer(-1));
						nonRoot = terms[0];
					}
			}

			if(root != NULL){
				Summation* conjucate = new Summation(root, nonRoot);
				Multiplication* n = new Multiplication(num, conjucate);
				Multiplication* d = new Multiplication(den, conjucate);
				Fraction* f = new Fraction(n,d);
				return f->calculate();
			}
		}
	}



	//Fractions

	if(typeid(*num) == typeid(Fraction)){
		Fraction* f = (Fraction*)num;
		num = new Multiplication(num, f->getDenominator());
		den = new Multiplication(den, f->getDenominator());
		return calculate();
	}

	if(typeid(*den) == typeid(Fraction)){
		Fraction* f = (Fraction*)den;
		num = new Multiplication(num, f->getDenominator());
		den = new Multiplication(den, f->getDenominator());
		return calculate();
	}


	//Logs

	if(typeid(*num) == typeid(Logarithm) && typeid(*den) == typeid(Logarithm)){
		Logarithm* n = (Logarithm*)num;
		Logarithm* d = (Logarithm*)den;

		if(n->getBase()->equals(d->getBase())){
			Logarithm* log = new Logarithm(d->getArg(), n->getArg());
			return log->calculate();
		}

	}





	//Multiplication


	if(typeid(*num) == typeid(Multiplication) || typeid(*den) == typeid(Multiplication)){


	Number** numTerms;
	Number** denTerms;

	int numSize = 1;
	int denSize = 1;

	if(typeid(*num) == typeid(Multiplication)){
		numTerms = ((Multiplication*)num)->getTerms();
		numSize = ((Multiplication*)num)->getSize();
	}
	else
		numTerms = &num;

	if(typeid(*den) == typeid(Multiplication)){
		denTerms = ((Multiplication*)den)->getTerms();
		denSize = ((Multiplication*)den)->getSize();
	}
	else
		denTerms = &den;

	for(int i = 0 ; i < numSize; i++){
		for(int j = 0; j < denSize; j++){
			reduceNumbers(&numTerms[i], &denTerms[j]);
		}
	}

	num = num->calculate();
	den = den->calculate();
	}





	//Check one last time for special cases

	// 0

	if(typeid(*num) == typeid(Integer))
		if(((Integer*)num)->getInteger() == 0)
			return new Integer(0);

	//1

	if(num->equals(den))
		return new Integer(1);


	//den = 1

	if(typeid(*den) == typeid(Integer))
			if(((Integer*)den)->getInteger() == 1)
				return num->calculate();




	return this;
}


bool Fraction::reduceInts(Integer& n, Integer& d){

	bool changed = false;;

	vector<int> nFactors = n.getFactors();

	vector<int> dFactors = d.getFactors();

	for(int i = 0; i < nFactors.size(); i++){
		for(int j = 0; j < dFactors.size(); j++){
			if(nFactors[i] == dFactors[j]){
				nFactors[i] = 4;
				dFactors[j] = 4;
				changed = true;
			}
		}
	}

	int numValue = 1;
	int denValue = 1;

	for(int i = 0; i < nFactors.size(); i++){
		if(nFactors[i] != 4)
		numValue *= nFactors[i];
	}


	for(int i = 0; i < dFactors.size(); i++){
		if(dFactors[i] != 4)
		denValue *= dFactors[i];
	}

	n = Integer(numValue);
	d = Integer(denValue);

	return changed;
}


bool Fraction::reduceNumbers(Number** nP, Number** dP){



	Number* n = *nP;
	Number* d = *dP;

	//Same:

	if(n->equals(d)){
		n = new Integer(1);
		d = new Integer(1);
		*nP = n;
		*dP = d;
		return true;
	}

	//Int:

	if(typeid(*n) == typeid(Integer) && typeid(*d) == typeid(Integer)){

		if(reduceInts(*(Integer*)n, *(Integer*)d))
			return true;

	}


	if(typeid(*n) == typeid(Exponent) || typeid(*d) == typeid(Exponent)){


		Exponent* n1 = NULL;
		Exponent* d1 = NULL;

		if(typeid(*n) == typeid(Exponent))
			n1 = (Exponent*)n;
		else
			n1 = new Exponent(n, new Integer(1));

		if(typeid(*d) == typeid(Exponent))
			d1 = (Exponent*)d;
		else
			d1 = new Exponent(d, new Integer(1));


		if(n1->getInside()->equals(d1->getInside())){
			Multiplication* mult = new Multiplication(d1->getPower(), new Integer(-1));
			Number** terms = new Number*[2];
			terms[0] = n1->getPower();
			terms[1] = mult;
			Summation* p = new Summation(terms, 2);
			n1 = new Exponent(n1->getInside(), p);
			n = n1;
			d = new Integer(1);

			*nP = n;
			*dP = d;
			return true;
		}


	}

	return false;

}





Number* Fraction::getNumerator(){
	return num;
}

Number* Fraction::getDenominator(){
	return den;
}


double Fraction::getDecimal(){
	return num->getDecimal() / den->getDecimal();
}


string Fraction::getString(){
	ostringstream stream;




	string s = typeid(*num).name();
	string s1 = typeid(*den).name();

	if((s != typeid(Integer).name()) && s != typeid(Constant).name())
		stream << "(";

	stream << num->getString();

	if((s != typeid(Integer).name()) && s != typeid(Constant).name())
			stream << ")";

	stream << "/";

	if((s1 != typeid(Integer).name()) && s1 != typeid(Constant).name())
			stream << "(";

	stream << den->getString();

	if((s1 != typeid(Integer).name()) && s1 != typeid(Constant).name())
				stream << ")";

	return stream.str();
}


bool Fraction::equals(Number* number){

	if(number == NULL)
		return false;

	if(typeid(*number) != typeid(Fraction))
		return false;
	Fraction* f = (Fraction*)number;

	Number* num1 = this->num;
	Number* num2 = f->num;
	Number* den1 = this->den;
	Number* den2 = f->den;

	return num1->equals(num2) && den1->equals(den2);
}



Fraction::~Fraction(){
	delete num;
	delete den;
}
