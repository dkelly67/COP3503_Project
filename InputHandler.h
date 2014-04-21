/*
 * InputHandler.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Jackson
 */

#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <string>

#include "Integer.h"
#include "Number.h"
#include "Root.h"
#include "Logarithm.h"



class InputHandler {
public:

	Number* parseString(string str);

	InputHandler();
	virtual ~InputHandler();



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
