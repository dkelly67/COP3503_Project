/*
 * Integer.h
 *
 *  Created on: Apr 6, 2014
 *      Author: Jackson
 */

#ifndef INTEGER_H_
#define INTEGER_H_

#include <vector>
#include "Number.h"

using namespace std;

class Integer : Number {
public:

	Integer(int i);

	virtual Number* calculate();
	virtual string getString();
	virtual double getDecimal();

	int getInteger();
	vector<int> getFactors();

	virtual ~Integer();

private:
	int theInteger;

	void getFactors(int theInt, vector<int>*);
};





#endif /* INTEGER_H_ */
