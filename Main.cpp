/**************************************************
Created by: Jackson Benfer,Daniel Kelly, Ross Castillo, Michael Ton, Alexa Chasar
Assignment: COP3503 Calculator Project
*****************************************************/

#include "Number.h"
#include "InputHandler.h"
#include "Integer.h"
#include "Summation.h"
#include "Multiplication.h"
#include "Root.h"
#include "Logarithm.h"
#include "Exponent.h"
#include "Constant.h"
#include "Fraction.h"

using namespace std;

vector<Number*> prevAns;
Number* ansKeyword;
InputHandler in;

void compNewExpression()
{
	string input;
	char direction;

	while (true)
	{


		cout << "Enter expression: ";

		cin >> input;
		if (input == "q")
		{
			cout << "Returning to menu" << endl;
			break;
		}
		Number *tempAns = in.parseString(input);

		Number *answer = tempAns->calculate();

		prevAns.push_back(answer);

		cout << "Answer: " << answer->getString() << endl;
	}
}

void help()
{
	char choice;
	while (true)
	{
		cout << "HELP MENU" << endl << "Choose what you need help with from the options below: " << endl;
		cout << "(a) What does 'Compute new expression' do?" << endl << "(b) What does the 'Review' function do?" << endl << "(c) How do I input an expression?" << endl << "(d) How do I input constants?" << endl << "(e) How do I input exponents?" << endl << "(f) How do I input logarithms?" << endl << "(g) How do I input roots?" << endl << "(h) How do I input fractions?" << endl;
		cin >> choice;

		switch (choice)
		{
		case 'a':
			cout << "Compute new expression allows you to enter a new expression to be calculated. You can enter an expression, such as 3 + 4, and it will display the answer for you, in this case, 7." << endl
				<< "However, try not to use any spaces.";
			break;
		case 'b':
			cout << "The Review funtion allows you to view previous answers to expressions you have entered in the past since you started the program." << endl
				<< "The user can also set the value of the 'ans' keyword within this function." << endl;
			break;
		case 'c':
			cout << "You can enter an expression just like you would on a regular calculator. Simply enter values that are seperated by operators such as '+', '-', '/', and/or '*'." << endl
				<< "However, there are special ways of entering constants, exponents, logarithms and roots into the expression. Explore the help menu for more specific instructions on this." << endl;
			break;
		case 'd':
			cout << "The only supported constants are 'pi' and 'e'. Simply enter 'pi' for PI and 'e' for the exponential constant." << endl;
			break;
		case 'e':
			cout << "Input exponents like so: Base^Power, in which 'Base' is a number and 'Power' is a number." << endl;
			break;
		case 'f':
			cout << "Input logarithms like so: 'log_Base:Arg', where 'Base' is the base of the logarithm and 'Arg' is the argument of the logarithm." << endl;
			break;
		case 'g':
			cout << "To enter a square root: 'sqrt:arg', in which 'arg' is the number that you are taking a square root of." << endl
				<< "To enter an nth root of a number: 'nrt:arg' , in which 'n' is an integer and 'arg' is the number that you are taking the nth root of." << endl;
			break;
		case 'h':
			cout << "To enter fractions, just use the '/' operator, where the numerator is on the left and the denominator is on the right side of the operator." << endl;
			break;
		case 'q':
			cout << "Back to menu" << endl;
			return;
		default:
			cout << "Not a help menu option. Please choose a valid help menu option." << endl;
			break;
		}
	}
}

void Review()
{	
	int i = 0;
	char rev;
	int ansNumber;
	while (true)
	{
		cout << "Choose an option below: " << endl;

		cout << "(a) Show decimal form of the previous expression's answer" << endl << "(b) Set the ans keyword to one of the previous expression's answer." << endl;

		cin >> rev;
		switch (rev)
		{
		case 'a':
			cout << "Which answer do you want to see?";
			cin >> ansNumber;
			if (ansNumber > prevAns.size() || ansNumber < 0)
			{
				cout << "That answer does not exist." << endl;
				break;
			}
			cout << prevAns[prevAns.size() - ansNumber]->getDecimal() << endl;
			break;
		case 'A':
			cout << "Which answer do you want to see?";
			cin >> ansNumber;
			if (ansNumber > prevAns.size() || ansNumber < 0)
			{
				cout << "That answer does not exist." << endl;
				break;
			}
			cout << prevAns[prevAns.size() - ansNumber]->getDecimal() << endl;
			break;
		case 'b':
			cout << "What previous answer do you want to set 'ans' to? ";
			cin >> ansNumber;
			in.setAns(prevAns[prevAns.size() - ansNumber]);
			break;
		case 'B':
			cout << "What previous answer do you want to set 'ans' to? ";
			cin >> ansNumber;

			in.setAns(prevAns[prevAns.size() - ansNumber]);
			break;
		case 'q':
			cout << "Returning to menu" << endl;
			return;
		default:
			cout << "Please choose a valid option";
			break;
		}
	}
}
void menu(void)
{
	while (true)
	{
		cout << "Hello! Please choose an option below." << endl;

		cout << "(a) Computer new expression" << endl << "(b) Help" << endl << "(c) Review previous expressions and answers" << endl << "(d) Quit" << endl;

		char choice;

		cin >> choice;

		switch (choice)
		{
		case 'a':
			cout << "Computing new expression" << endl;
			compNewExpression();
			break;
		case 'A':
			cout << "Computing new expression" << endl;
			compNewExpression();
			break;
		case 'b':
			cout << "Going to the help page!" << endl;
			help();
			break;
		case 'B':
			cout << "Going to the help page!" << endl;
			help();
			break;
		case 'c':
			cout << "Reviewing previous activity" << endl;
			Review();
			break;
		case 'C':
			cout << "Reviewing previous activity" << endl;
			Review();
			break;
		case 'd':
			cout << "Quitting..." << endl;
			return;
		case 'D':
			cout << "Quitting..." << endl;
			return;
		default:
			cout << "DUMBASS" << endl;
			break;
		}
	}
}

int main(void)
{	

	menu();

	return 0;
}