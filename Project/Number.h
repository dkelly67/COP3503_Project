/*
 * Number.h
 *
 *  Created on: Apr 6, 2014
 *      Author: Jackson
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include <string>

using namespace std;

class Number {
public:
	virtual ~Number(){};

	virtual Number* calculate() = 0;
	virtual string getString() = 0;
	virtual double getDecimal() = 0;
};


#endif /* NUMBER_H_ */







