/*
 * Constant.h
 *
 *  Created on: Apr 6, 2014
 *      Author: Jackson
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_

#include "Number.h";


class Constant : public Number{
public:

	Constant(bool isPi, bool isE);
	virtual ~Constant();

	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();


	bool IsPi();
	bool IsE();

private:
	bool pi;
	bool e;
};





#endif /* CONSTANT_H_ */
