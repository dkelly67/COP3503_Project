//============================================================================
// Created on  : 04.12.14
// File        : Menu.cpp
// Description : This class presents the menu for user interaction.
//============================================================================

#include "Number.h"

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;


std::vector<Number*> prevAns;
Number* ans;

void help() {
	int j;
	cout << "Welcome to the help section!" << endl;
	cout << "For help with abbreviations press 1." << endl;
	cout << "For help with the different expressions press 2." << endl;
	cout << "For help with available functions press 3." << endl;
	cout << "Press any other number to quit." << endl;
	cin >> j;
	while (j==1 || j==2 || j==3){
		if(j==1){
			cout << "sqrt:x is the square root of x." << endl;
			cout << "nrt:x is for the nth root of x." << endl;
			cout << "log_b:x is the log base b of x." << endl;
			cout << "ans enables you to use a previous answer in an expression by selecting one through the Review function." << endl;
		}
		else if(j==2){
			cout << "Constants are either pi or e. Other constants are not valid in this program." << endl;
			cout << "Summation is used to show the addition or subtraction of a number to a constant or another number." << endl;
			cout << "Multiplication is used to show the multiplication of a number to a constant or another number." << endl;
			cout << "An Exponent has two parts, a base number and the power it is being multiplied too." << endl;
			cout << "A Fraction consists of both a numerator and a denominator, which are calculated separately." << endl;
			cout << "A Logarithm requires a number and a base of that number." << endl;
		}
		else if(j==3){
			cout << "The Review function can show all previous expressions made in the program. It can also save one in 'ans' to be used in a new expression." << endl;
			cout << "Compute New Expression is used to create any type of expression." << endl;
			cout << ".getDecimal() can be used to return your expression in decimal form." << endl;
			cout << ".getString() can be used to return your expression as a string." << endl;
		}
		cout << "For help with abbreviations press 1." << endl;
		cout << "For help with the different expressions press 2." << endl;
		cout << "For help with available functions press 3." << endl;
		cout << "Press any other number to quit." << endl;
		cin >> j;
	}
}

void compNewExpression(){
	string str;
	cout << "Enter the expression." << endl;
	cin >> str;
	cout << prevAns.insert(prevAns.begin(), inputHandler(str));
	str = NULL;
	cout << "\nEnter another expression or enter 'back' to return to the menu." << endl;
	cin >> str;
	while (str.substr(0)!='back'){
		cout << prevAns.insert(prevAns.begin(), inputHandler(str));
		str = NULL;
		cout << "\nEnter another expression or enter 'back' to return to the menu." << endl;
		cin >> str;
	}
}

void review(vector<Number*> prevAns){
	int num, a, count, i, n;
	double d;
	//std::ostringstream s2;
	string s;
	cout << "Enter the number of answers you wish to step back (ex: pressing 2 will display your second to last expression." << endl;
	cout << "Alternatively, press -1 to display all previous answers." << endl;
	cout << "Enter 0 to go back." << endl;
	cin >> num;
	while(num!=0){
		if (num>=prevAns.size()){
			throw out_of_range("Entered value exceeds answer history");
		}
		else if (num==-1){
			for(int i=0; i<prevAns.size(); i++){
				cout << i+":   "+prevAns[i];
			}
		}
		else{
			cout << prevAns[num];
			cout << "To be able to use this answer in another equation press 1." << endl;
			cout << "To view the answer as a decimal in floating point form press 2." << endl;
			cout << "Otherwise press any other number." << endl;
			cin >> a;
			if (a==1) ans==prevAns[num];
			if (a==2){
				d = prevAns[num]->getDecimal();
				s << d;
				//s = s2;
				if (d>0 && d<10) cout << d+"e0" << endl;
				else if (d>10){
					i = s.find('.');
					while (i>1){
						std::swap(s[i-1],s[i]);
						i--;
						count++;
					}
					cout << s+"e"+count;
					count = 0;
				}
				else if (d<0){
					i = s.find('.');
					for (int j=0; j<s.length(); j++){
						if(s[j]!=0 && s[j]!='.'){
							n = j;
							break;
						}
					}
					while(i<n){
						std::swap(s[i],s[i+1]);
						i++;
						count--;
					}
					cout << s+"e"+count;
					count = 0;
				}
			}
		}
		cout << "Enter the number of answers you wish to step back (ex: pressing 2 will display your second to last expression." << endl;
		cout << "Alternatively, press -1 to display all previous answers." << endl;
		cout << "Enter 0 to go back." << endl;
		cin >> num;
	}
}

void menu() {
	//Options: Compute new expression, help, review, quit
	int i;
	cout << "Welcome to the menu!" << endl;
	cout << "To create a new expression, press 1." << endl;
	cout << "To review all previous expression, press 2." << endl;
	cout << "To view help on how to use this program, press 3." << endl;
	cout << "Press any other number to quit." << endl;
	cin >> i;
	while(i==1 || i==2 || i==3){
		if(i==1) compNewExpression();
		else if(i==2) review(prevAns);
		else if(i==3) help();
		cout << "To create a new expression, press 1." << endl;
		cout << "To review all previous expression, press 2." << endl;
		cout << "To view help on how to use this program, press 3." << endl;
		cout << "Press any other number to quit." << endl;
		cin >> i;
	}
}
