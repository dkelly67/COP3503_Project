//============================================================================
// Author      : Ross Castillo
// Created on  : 04.13.14
// File        : Root.h
// Description : This class will represent the square root function.
//============================================================================

#include "Root.h"
#include "Integer.h"
#include "Multiplication.h"
#include "Number.h"

#include <vector>
#include <sstream>
#include <stdexcept>
#include <algorithm> // sort()
#include <math.h> // pow()

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
	string insideType = typeid(inside).name();

	if (inside < 0) {
		throw out_of_range("The inside of a square root must be positive");
	}

	if (root < 0) { // If negative root, change to one over its positive root

	}
	else if (root == 1) { // If root is one, return inside as is
		return inside;
	}


	if (insideType == "class Integer") {

		// Cast inside to actually be an integer
		Integer* i = (Integer*) inside;

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

		// inside = (inside) / (outside)^root;
		Root* r = new Root((new Integer(i->getInteger()/answer)), root);

		Number** terms = new Number*[2];
		terms[0] = new Integer(outside);
		terms[1] = r;

		return new Multiplication(terms, 2);
	}
	else if (insideType == "Constant") {
		return this;
	}
	/////////////////////////////////////////////////////////
	else if (insideType == "Exponent") {

	}
	else if (insideType == "Fraction") {

	}
	else if (insideType == "Logarithm") {

	}
	else if (insideType == "Root") {

	}
	/////////////////////////////////////////////////////////

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
	return false;
}

Root::~Root() {
}
