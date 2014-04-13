

#include <sstream>
#include <typeinfo>
#include <iostream>
#include "Fraction.h"
#include "Integer.h"
#include "Constant.h"
#include <vector>

using namespace std;

Fraction::Fraction(Number* num, Number* den){
	this->num = num;
	this->den = den;
}


Number* Fraction::calculate(){

	if(num->equals(den))
		return new Integer(1);


	//Multiplicaion
	//Rationalize denominator
	//Reduce Summation



	if(typeid(*num) == typeid(Integer) && typeid(*den) == typeid(Integer)){

		//Reduce integers

		Integer* n = (Integer*) num;
		Integer* d = (Integer*) den;

		reduceInts(*n, *d);

		//delete this;

		if(d->getInteger() != 1)
			return new Fraction(n, d);
		else return new Integer(d->getInteger());
	}


	return this;
}


void Fraction::reduceInts(Integer& n, Integer& d){

	vector<int> nFactors = n.getFactors();

	vector<int> dFactors = d.getFactors();

	//TODO: Really hacky way of doing this


	for(int i = 0; i < nFactors.size(); i++){
		for(int j = 0; j < dFactors.size(); j++){
			if(nFactors[i] == dFactors[j]){
				nFactors[i] = 4;
				dFactors[j] = 4;
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
