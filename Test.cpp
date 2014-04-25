/*
#include "Menu.cpp"

int main(){

	menu();


	InputHandler* ih = new InputHandler();

	Number* num;


	try{
		num = ih->parseString("2 ^ (5/3 + pi) / (3rt:4)");
		cout << "Entered: " << num->getString() << endl;
		num = num->calculate();
		num = num->calculate();
		cout << "Result: " << num->getString()<< endl;

	}catch(out_of_range& e){
		cout << e.what() << endl;
	}


	return 0;
}
*/


