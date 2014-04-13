//============================================================================
// Author      : Ross Castillo
// Created on  : 04.13.14
// File        : Root.h
// Description : This class will represent the square root function.
//============================================================================

#include "Root.h"
#include "Integer.h"
#include "Multipication.h"

#include <math.h> // For pow()
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
		vector<int> v = getFactors(i, v); // Creating a new vector v and then using it in getFactors()

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
		for (unsigned int i = 0; i < root ; i++ ) {
			answer *= outside;
		}

		Root* r = new Root(root,new Integer (i->getInteger()/answer));

		Number** terms = {new Integer(outside), r};

		return new Multipication(terms);
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

Root::~Root() {
}
