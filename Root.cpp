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

#include <math.h> // For power()
#include <vector>
#include <sstream>
#include <stdexcept> // For throwing out_of_range exceptions
#include <algorithm> // For sort()

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

		Integer* i = (Integer*) inside; // Cast inside to actually be an integer
		vector<int> v = i->getFactors(); // Creating a new vector v and then using it in getFactors()

		sort(v.begin(), v.end()); // Arranging the elements of vector v in ascending numerical order

		int count = 0; // Count variable to keep track of like factors
		int current = 0; // Variable we're looking for
		int outside = 1; // Outside of square root has 1

		for (unsigned int i = 0; i <= v.size(); i++) { // Iterate through the vector one at a time
			if (current != v[i]) {
				current = v[i]; // Set the current index to the current variable
				count = 1;
			}
			else {
				count++;
				if (count == root) {
					outside = outside * current;
					count = 0;
				}
			}
		} // End of for-loop

		// inside = (inside) / (outside)^root;
		int answer = 1;
		for (int i = 0; i < root ; i++ ) {
			answer *= outside;
		}

		Root* r = new Root(new Integer (i->getInteger()/answer), root);

		Number** terms = new Number*[2];
		terms[0] = new Integer(outside);
		terms[1] = r;

		return new Multiplication(terms, 2);
	}

	/////////////////////////////////////////////////////////
	else if (insideType == "Exponent") {

	}
	else if (insideType == "Constant") {
		return this;
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
