#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "Root.h"
#include "Number.h"
#include "Integer.h"
#include "Fraction.h"
#include "Exponent.h"
#include "Constant.h"
#include "Summation.h"
#include "Logarithm.h"
#include "Multiplication.h"

#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

class InputHandler {
public:

	Number* parseString(string str);

	InputHandler();
	virtual ~InputHandler();

	void setAns(Number* ans);

private:

	Number* ans;

	Number* parseString(string str, int start, int end);

	Number* parseParenthesis(string str, int start, int& j);

	Number* readNumber(string str, int i, int& j);
	Number* readInteger(string str, int i, int& j);

	void addParenthesis(string& str, char op1, char op2);
	void addMultiplication(string& str);

	bool checkFormat(string str);

	bool isInt(char c);
	bool isOperator(char c);
};


#endif /* INPUTHANDLER_H_ */
