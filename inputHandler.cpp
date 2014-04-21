/*
 * InputHandler.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: Jackson
 */

#include "InputHandler.h"

#include <sstream>
#include <stdexcept>

#include "Constant.h"
#include "Exponent.h"
#include "Fraction.h"
#include "Multiplication.h"
#include "Summation.h"

class Logarithm;
class Root;




InputHandler::InputHandler() {
	ans = NULL;
}

Number* InputHandler::parseString(string str){

	checkFormat(str);

	for(int i = 0; i < str.length(); i++){
		if(isOperator(str.at(i))){
			if(str.at(i) != '-')
				str.insert(0, "ans");
			else
				str.insert(0, "0");//Assume leading - is a negative sign
			break;
		}
		else if(str.at(i) != ' ')
			break;
	}

	//Add implicit *

	addMultiplication(str);

	//Add implicit parenthesis (for pemdas)
	addParenthesis(str, '^', 0);
	addParenthesis(str, '*', '/');


	ans = parseString(str, 0, str.length());
	return ans;
}


bool InputHandler::checkFormat(string str){

	int counter = 0;
	bool lastOperator = false;
	for(int i = 0; i < str.length(); i++){
		char c = str.at(i);

		//Parenthesis
		if(c == '(')
			counter++;
		if(c == ')'){
			if(lastOperator)
				throw out_of_range("Trailing operator within parenthesized expression");
			counter--;
		}

		//Operators
		if(isOperator(c)){
			if(lastOperator && c != '-')
				throw out_of_range("Subsequent operators not allowed");
			lastOperator = true;
		}
		else if(c != ' ')
			lastOperator = false;
	}

	if(counter != 0)
		throw out_of_range("Improper use of parenthesis");

	if(lastOperator)
		throw out_of_range("Trailing Operator");



	return true;
}


void InputHandler::addMultiplication(string& str){
	for(int i = 0; i < str.length(); i++){
		if(str.at(i) == '('){
			for(int j = i-1; j >= 0; j--){
				if(isOperator(str.at(j)) || str.at(j) == ':')
					break;
				else if(str.at(j) != ' '){
					str.insert(j+1, "*");
					i++;
					break;
				}
			}
		}
		if(str.at(i) == ')'){
			for(int j = i+1; j < str.length(); j++){
				if(isOperator(str.at(j)))
					break;
				else if(str.at(j) != ' '){
					str.insert(j, "*");
					i++;
					break;
				}
			}
		}
	}
}


void InputHandler::addParenthesis(string& str, char op1, char op2){

	int counter = 0;

	for(int i = 0; i < str.length(); i++){
		if(str.at(i) == op1 || str.at(i) == op2){
			//Left
			counter = 0;
			for(int j = i-1; j >=0; j--){
				if(str.at(j) == ')')
					counter++;
				else if(str.at(j) == '(')
					counter--;
				if(counter == -1)
					break;
				else if(isOperator(str.at(j)) && counter == 0){
					str.insert(j+1, "(");
					i++;
					break;
				}
				if(j == 0){
					str.insert(0, "(");
					i++;
					break;
				}
			}

			//Right
			counter = 0;
			for(int j = i+1; j < str.length(); j++){
				if(str.at(j) == '(')
					counter++;
				else if(str.at(j) == ')')
					counter--;
				if(counter == -1)
					break;
				else if(isOperator(str.at(j)) && counter == 0){
					str.insert(j, ")");
					break;
				}
				if(j == str.length()-1){
					str.append(")");
					break;
				}

			}
		}
	}
}


Number* InputHandler::parseString(string str, int start, int end){

	Number* num;
	Number* newNum;
	int j = 1;
	char op = ' ';

	for(int i = start; i < end; i+=j){

		j = 1;

		char c = str.at(i);

		if(c != ' ' && !isOperator(c)){

			//Must be a number
			newNum = readNumber(str, i, j);

			if(op == '+')
				num = new Summation(num, newNum);
			else if(op == '-')
				num = new Summation(num, new Multiplication(new Integer(-1), newNum));
			else if(op == '*')
				num = new Multiplication(num, newNum);
			else if(op == '/')
				num = new Fraction(num, newNum);
			else if(op == '^')
				num = new Exponent(num, newNum);
			else{
				num = newNum;
			}

			op = ' ';
		}
		if(isOperator(c)){
			op = c;
		}
		newNum = 0;
	}
	return num;
}


Number* InputHandler::parseParenthesis(string str, int start, int& j){

	int counter = 1;
	j = 1;
	for(int i = start + 1; i < str.length(); i++){
		j++;
		char c = str.at(i);
		if(c == '(')
			counter++;
		else if (c == ')')
			counter--;
		if(counter <= 0)
			return parseString(str, start+1, i);
	}
}


Number* InputHandler::readInteger(string str, int i, int& j){

	ostringstream stream;
	j = 0;
	for(; i < str.length(); i++){
			char c = str.at(i);
			if(isInt(c)){
				stream << c;
				j++;
			}
			//Found it convenient to handle 2pi, 2e, 2sqrt, and nrt here

			else if(str.substr(i, 3) == "rt:"){
				int a;
				string s = stream.str();
				istringstream (s) >> a;
				int one = 0;
				Number* num =  new Root(readNumber(str, i+3, one), a);
				j+= one + 3;
				return num;
			}
			else if(str.substr(i, 2) == "pi"){
				int a;
				string s = stream.str();
				istringstream (s) >> a;
				Number* num =  new Multiplication(new Integer(a), new Constant(true, false));
				j += 2;
				return num;
			}
			else if(str.substr(i, 5) == "sqrt:"){
				int a;
				string s = stream.str();
				istringstream (s) >> a;
				int one = 0;
				Number* num =  new Multiplication(new Integer(a), new Root(readNumber(str, i+5, one), 2));
				j += one + 5;
				return num;
			}
			else if(c == 'e'){
				int a;
				string s = stream.str();
				istringstream (s) >> a;
				int one = 0;
				Number* num =  new Multiplication(new Integer(a), new Constant(false, true));
				j++;
				return num;
			}else{
				break;
			}
	}
	int a;
	string s = stream.str();
	istringstream (s) >> a;
	return new Integer(a);
}






Number* InputHandler::readNumber(string str, int i, int& j){


	char c = str.at(i);
	Number* newNum;
	j = 0;


	//int
	if(isInt(c))
		newNum = this->readInteger(str, i, j);
	//pi, e

	if(c == 'p')
	if(str.at(i + 1) == 'i') {
		newNum = new Constant(true, false);
		j = 2;
	}

	if(c == 'e'){
		newNum = new Constant(false, true);
		j = 1;
	}

	//Log
	if(str.substr(i, 4) == "log_"){
		int one;
		Number* base = readNumber(str, i+4, j);
		one = j;
		Number* inside = readNumber(str, i+5+j, j);
		newNum = new Logarithm(base, inside);
		j += one + 5;
	}

	//Root
	if(str.substr(i, 5) == "sqrt:"){
		newNum = new Root(readNumber(str, i+5, j), 2);
		j += 5;
	}

	//ans
	if(str.substr(i, 3) == "ans"){
		newNum = ans;
		j = 3;
	}

	// Parenthesis

	if(c == '(')
		newNum = parseParenthesis(str, i, j);


	//Prevent infinie loops
	if(j == 0)
		j = 1;


	return newNum;
}



bool InputHandler::isInt(char c){
	int i = c - 48;

	if(i >= 0 && i <= 9)
		return true;
	else
		return false;
}

bool InputHandler::isOperator(char c){
	return (c == '+' || c == '/' || c == '*' || c == '-' || c == '^');
}



InputHandler::~InputHandler() {
}

