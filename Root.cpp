//============================================================================
// Created on  : 04.13.14
// File        : Root.h
// Description : This class will represent the square root function.
//============================================================================

#include "Root.h"
#include "Number.h"
#include "Integer.h"
#include "Exponent.h"
#include "Multiplication.h"

#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm> // sort()
#include <math.h> // pow() for getDecimal()

Root::Root(Number* inside, int root) {
	this->inside = inside;
	this->root = root;
}

Number* Root::getInside() {
	return inside;
}

int Root::getRoot() {
	return root;
}

Number* Root::calculate() {

	// Calculate the inside first before anything
	inside = inside->calculate();

	// Necessary checks
	if (inside < 0) {
		throw out_of_range("The inside of a square root must be positive");
	}
	if (root < 0) {
		// Make an integer of 1 for the numerator
		Integer* newNum = new Integer(1);

		// Make the negative root positive
		root = root * (-1); // Possible because root is of type int

		// Making a new root with the now positive 'root'
		Root* negRt = new Root(inside, root);

		// Make a fraction with 1 over the positive square root
		Fraction* negRoot = new Fraction(newNum,negRt);

		negRoot->calculate();

		return negRoot;
	}
	else if (root == 1) { // If root is one, return inside as is
		return inside;
	}

	//////////////////////////////////////////////////////////////////////////
	if (typeid(*inside) == typeid(Integer)) {

		// Cast 'inside' to actually be an integer
		Integer* i = (Integer*) inside;

		// Check if 'inside' is one, if so return one
		if (i->getInteger() == 1) {
			return i;
		}

		// Creating a new vector v and then using it in getFactors()
		vector<int> v = i->getFactors();

		// Arranging the elements of vector v in ascending numerical order
		sort(v.begin(), v.end());

		int count = 0; // Count variable to keep track of like-factors
		int current = 0; // Variable we're looking for
		int outside = 1; // Outside of square root has 1

		for (unsigned int i = 0; i <= v.size(); i++) {
			if (current != v[i]) {
				current = v[i];
				count = 1;
			}
			else {
				count++;
				if (count == root) {
					outside = outside * current;
					count = 0;
				}
			}
		}


		// (outside)^root;
		int answer = 1;
		for (int i = 0; i < root ; i++ ) {
			answer *= outside;
		}

		int in = i->getInteger()/answer;

		if(outside != 1){
			if(in != 1){
				Root* r = new Root((new Integer(in)), root);
				return new Multiplication(new Integer(outside), r);
			}
			else
				return new Integer(outside);
		}
		else
			return this;
	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	else if (typeid(*inside) == typeid(Exponent)) {

		// Cast 'inside' to actually be an exponent
		Exponent* exp = (Exponent*) inside;

		Number* power = exp->getPower();

		if (typeid(power) == typeid(Integer*)) {

			// Casting 'power' to be an int
			Integer* i = (Integer*) power;

			int outsidePower = i->getInteger() / root;
			int insidePower = i->getInteger() % root;

			i = new Integer( ((i->getInteger()) / root) );

			Exponent* outside = new Exponent(inside, new Integer(outsidePower));
			Exponent* in = new Exponent(inside, new Integer(insidePower));

			Root* r = new Root(in, root);

			Multiplication* mult = new Multiplication(r, outside);

			return mult;
		}

		if (typeid(power) == typeid(Fraction*)) {

			// Casting 'power' to be a fraction
			Fraction* f = (Fraction*) power;

			Number* numerator = f->getNumerator();
			Number* denominator = f->getDenominator();

			int n;
			int d;

			if (typeid(*numerator) == typeid(Integer*)) {
				n = ((Integer*)numerator)->getInteger();

			}
			else {
				return this;
			}


			if (typeid(*denominator) == typeid(Integer*)) {
				d = ((Integer*)denominator)->getInteger();
			}
			else {
				return this;
			}

			Exponent* newExp = new Exponent(inside, new Integer(n));

			Root* rt = new Root(newExp, d * root);

			return rt->calculate();
		}
	}
	//////////////////////////////////////////////////////////////////////////
	else if (typeid(*inside) == typeid(Fraction)) {

		// Casting the inside number in the radical to be of type Fraction
		Fraction* f = (Fraction*) inside;

		// Now need to make both the numerator and the denominator their
		// own radical with the same root
		Number* top;
		Number* bottom;

		top = f->getNumerator();
		Root* numRt = new Root(top, root);


		bottom = f->getDenominator();
		Root* denRt = new Root(bottom, root);

		Fraction* radFrac = new Fraction(numRt, denRt);

		return radFrac->calculate();
	}
	//////////////////////////////////////////////////////////////////////////
	else if (typeid(*inside) == typeid(Root)) {

		// Casting the inside to be of type Root
		Root* r = (Root*) inside;

		int newRoot = 1;
		newRoot = newRoot * r->getRoot();


		// Making the new final root
		Root* finalRt = new Root(inside,newRoot);

		return finalRt->calculate();
	}
	//////////////////////////////////////////////////////////////////////////
	else if (typeid(*inside) == typeid(Multiplication)) {
		// Casting inside to multiplication
		Multiplication* m = (Multiplication*) inside;

		// Making my own array
		Number** radArray = new Number*[m->getSize()];

		// Make each term its own root
		for (unsigned int i = 0; i <= m->getSize(); i++) {
			radArray[i] = new Root((m->getTerms())[i], root);
		}

		return m->calculate();
	}
	//////////////////////////////////////////////////////////////////////////

	return this;
}

string Root::getString() {
	stringstream ss;

	if (root == 2) {
		ss << "sqrt:" << "(" << inside->getString() << ")";
		return ss.str();
	}
	else {
		ss << root << "rt:" << "(" << inside->getString() << ")";
		return ss.str();
	}
}

double Root::getDecimal() {
	return pow(inside->getDecimal(), (1.0/root));
}

bool Root::equals(Number* number){

	// See if it's a root
	if (typeid(*number) != typeid(Root)) {
		return false;
	}

	// If so, cast it to a root
	Root* r = (Root*)number;

	// Make sure insides are equal and roots are equal
	return(r->root == this->root && r->inside->equals(this->inside));
}

Root::~Root() {
}
