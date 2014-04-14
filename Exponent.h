#ifndef EXPONENT_H_
#define EXPONENT_H_

#include "Number.h"

using namespace std;

class Exponent : public Number{
public:
	Exponent(Number* inside, Number* power);

	virtual Number* calculate();
	virtual double getDecimal();
	virtual string getString();
	virtual bool equals(Number* number);

	Number* getInside();
	Number* getPower();


	virtual ~Exponent();

private:
	Number* inside;
	Number* power;
};

#endif /* EXPONENT_H_ */
