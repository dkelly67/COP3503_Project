/*
 * Fraction.h
 *
 *  Created on: Apr 11, 2014
 *      Author: Jackson
 */

#ifndef FRACTION_H_
#define FRACTION_H_

#include "Number.h"
#include "Integer.h"
#include "Exponent.h"

using namespace std;

class Fraction : public Number{
public:

	Fraction(Number* num, Number* den);

	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();
	virtual bool equals(Number* number);

	Number* getNumerator();
	Number* getDenominator();

	virtual ~Fraction();

private:
	Number* num;
	Number* den;

	bool reduceInts(Integer& n, Integer& d);
	bool reduceNumbers(Number** n, Number** d);
};


#endif /* FRACTION_H_ */
