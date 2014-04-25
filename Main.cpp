/**************************************************
Created by: Jackson Benfer,Daniel Kelly, Ross Castillo, Michael Ton, Alexa Chasar
Assignment: COP3503 Symbolic Calculator Project
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

//Global variables
vector<Number*> prevAns; //Stores previous answers. Used for "Reviewing" them later
//Number* ansKeyword; //
InputHandler in; //Inputhandler object that is used for taking in inputs and processing them

//Compute New Expression
void compNewExpression()
{
	string input;
	char direction;
	//Keeps asking for new inpu expression until user specifies 'q' meaning quit. User then returns back to original menu
	while (true)
	{


		cout << "Enter expression: ";

		cin >> input;
		if (input == "q")	//If input is 'q' then function breaks and user returns to menu
		{
			cout << "Returning to menu" << endl;
			break;
		}
		Number *tempAns = in.parseString(input); //parses input string ussing inputHandler object global variable

		Number *answer = tempAns->calculate(); //Calculates parsed input string

		prevAns.push_back(answer); //Adds this answer to the dynamic list of previous answers.

		cout << "Answer: " << answer->getString() << endl; //Output
	}
}

//HELP menu. Provides information on different functions and how to input
void help()
{
	char choice; 
	//loops through help menu until user decides to exit, in which case the user returns to the main menu
	while (true)
	{
		cout << "HELP MENU" << endl << "Choose what you need help with from the options below: " << endl;
		cout << "(a) What does 'Compute new expression' do?" << endl << "(b) What does the 'Review' function do?" << endl << "(c) How do I enter an expression?" << endl << "(d) How do I enter constants?" << endl << "(e) How do I enter exponents?" << endl << "(f) How do I enter logarithms?" << endl << "(g) How do I enter roots?" << endl << "(h) How do I enter fractions?" << endl;
		cin >> choice;
		//Based on choice, displays appropriate output
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
			cout << "Enter exponents like so: Base^Power, in which 'Base' is a number and 'Power' is a number." << endl;
			break;
		case 'f':
			cout << "Enter logarithms like so: 'log_Base:Arg', where 'Base' is the base of the logarithm and 'Arg' is the argument of the logarithm." << endl;
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
			return; //Returns to main menu
		default:
			cout << "Not a help menu option. Please choose a valid help menu option." << endl;
			break;
		}
	}
}

//Function which allows user to set 'ans' keyword and review previous answers to previously entered expressions.
void Review()
{	
	int i = 0;
	char choice;
	int ansNumber;
	//Loops through choices in the Review menu, until user specifies a quit command, in which the user returns to the main menu
	while (true)
	{
		cout << "Choose an option below: " << endl;

		cout << "(a) Show decimal form of the previous expression's answer" << endl << "(b) Set the ans keyword to one of the previous expression's answer." << endl;

		cin >> choice;
		switch (choice)
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
			return; //Return to main menu
		default:
			cout << "Please choose a valid option";
			break;
		}
	}
}
//Main menu. Displays options for the user to execute. Options are, computing a new expression, help menu, and reviewing previous answers
void menu(void)
{
	//Loops through choices until user specifies quit command, in which the program exits
	while (true)
	{
		cout << "Hello! Please choose an option below." << endl;

		cout << "(a) Compute new expression" << endl << "(b) Help" << endl << "(c) Review previous expressions and answers" << endl << "(d) Quit" << endl;

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
			cout << "Not a valid option. Please use a valid option." << endl;
			break;
		}
	}
}

//Main function
int main(void)
{	

	menu();

	return 0;
}