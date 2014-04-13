/*
 * Fraction.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Jackson
 */

#ifndef FRACTION_H_
#define FRACTION_H_

#include "Number.h"

using namespace std;

class Fraction : public Number{
public:

	Fraction(Number* num, Number* den);

	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();

	Number* getNumerator();
	Number* getDenominator();

	virtual ~Fraction();

private:
	Number* num;
	Number* den;


};


#endif /* FRACTION_H_ */
