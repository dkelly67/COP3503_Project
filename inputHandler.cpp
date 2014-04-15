#include <cmath>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////
class Equation {

public:
        Equation();//default constructor
        ~Equation();//default destructor

        void reversePolishNotation(); //main method
        void set(string); //main method


        double Evaluate(vector <string> &s);
        void Convert(const string &Infix, string &ReversePoli);
        bool ChecksPrecedence(char Op1, char Op2);
        bool IsAnOperand(char ch);
        bool IsAnOperator(char ch);
        bool IsNumber(char ch);
        string Change(string);
        string InsertSpace(string);
        bool CheckValid(string);
        void Next(string);

private:
        string Infix;
};
////////////////////////////////////////////////////////////////


Equation::Equation() {
  Infix = "";
}

Equation::~Equation(){
}

//a set method
void Equation::set(string a){
    Infix = a;
}

bool Equation::IsAnOperand(char ch)
{
   if (
       ((ch >= '0') && (ch <= '9'))||
       (ch == 'v') ||
       (ch == 'y') ||
       (ch == '.')
       )
      return true;
   else
      return false;
}

bool Equation::IsNumber(char ch){
   if (((ch >= '0') && (ch <= '9'))||(ch == '.'))
       return true;
    else
       return false;
}

bool Equation::IsAnOperator(char ch)
{
    if ((ch == '+') ||
        (ch == '-') ||
        (ch == '*') ||
        (ch == '/') ||
        (ch == '^'))
        return true;
     else
        return false;
}


bool Equation::ChecksPrecedence(char Op1, char Op2){
   if (Op1== '(')
      return false;
   else if (Op2 == '(')
      return false;
   else if (Op2 == ')')
      return true;
   else if ((Op1 == '^') && (Op2== '^'))
      return false;
   else if (Op1 == '^')
      return true;
   else if (Op2 == '^')
      return false;
   else if ((Op1 == '*') || (Op1 == '/'))
      return true;
   else if ((Op2 == '*') || (Op2 == '/'))
      return false;
   else
      return true;
}

void Equation::Convert(const string &Infix, string &ReversePoli){
   stack <char> OperatorStack;
   char TopSymbol, Symbol;
   int k;

   for (k=0; k<Infix.size(); k++){
      Symbol = Infix[k];
      if (IsAnOperand(Symbol))
         ReversePoli = ReversePoli + Symbol;
      else{
         while ((!OperatorStack.empty()) && (ChecksPrecedence(OperatorStack.top(), Symbol))){
            TopSymbol = OperatorStack.top();
            OperatorStack.pop();
            ReversePoli = ReversePoli + TopSymbol;
            }
         if ((!OperatorStack.empty()) && (Symbol == ')'))
            OperatorStack.pop();
         else
            OperatorStack.push(Symbol);
      }
   }

   while (!OperatorStack.empty()){
      TopSymbol = OperatorStack.top();
      OperatorStack.pop();
      ReversePoli = ReversePoli + TopSymbol;
   }
}

string Equation::Change(string tmp){
    for(int i=0; i<tmp.length(); i++){
      if(IsNumber(tmp[i])==true){
          if(IsNumber(tmp[i+1])==false){
              tmp.insert(i+1, "v");
          }
      }
    }
    for (int i=0; i<tmp.length(); i++){
        if(tmp[i]=='-'){
            if((tmp[i-1]!='v')&&(tmp[i-1]!=')')){
               tmp.replace(i,1,"y");
            }
        }
    }
    return tmp;
}

string Equation::InsertSpace(string tmp)
{
    for(int i=0; i<tmp.length(); i++){
         if(IsAnOperator(tmp[i])==true){
            tmp.insert(i+1, " ");
            //Inserts a space after an operator is found
          }
           else if( tmp[i]=='v' ){
              tmp.replace(i,1," ");
              //replaces any v with a space
           }
    }

    for(int i = 0; i<tmp.length(); i++){
        if(tmp[i]=='y'){
             tmp.replace(i,1,"-");
        }
     }
    return tmp;
}

bool Equation::CheckValid(string tmp){
    for(int i=0; i<tmp.length(); i++){
        if((tmp[i]=='+')||(tmp[i]=='-')){
            if((tmp[i+1]=='+')||(tmp[i+1]=='-')){
                return false;
            }
        }
    }

    string array = "0123456789+-*/^().";

    int count = 0;
    for(int i=0; i<tmp.length(); i++){
        for(int j=0; j<array.length(); j++){
            if(tmp[i]==array[j]){
               count++;
            }
        }
    }

    if(count==tmp.length()){
      return true;
    }
    else{
      return false;
    }

}

void Equation::Next(string tmp){
  vector <string> array;

  int spaces = 0;
  for (int a=0; a<tmp.length(); a++ ){
      if(tmp[a]==' '){
          spaces++;
      }
  }
   string token;
   istringstream iss(tmp);
   while(getline(iss, token, ' ') ){
      array.push_back(token);
   }
  //this initializes the stack
  stack <string> my_stack;
  vector <string> temp;
  string ch;

  for(int i=0; i<spaces; i++){
      string s;
      s = array[i]; //make it easier to read

      if((s!="+")&&(s!="*")&&(s!="-")&&(s!="^")&&(s!="/")){
        my_stack.push(s);//pushes numbers onto the stack
      }
         else{//if an operator is found instead
            my_stack.push(s);//pushes the operator onto stack

               for(int i=0; i<3; i++ ){
                 temp.push_back(my_stack.top());
                 my_stack.pop(); //removes from the stack
               }

               double z;
               z = Evaluate(temp);
               ostringstream outs;
               outs << z;   // Converts value into a string.
               ch = outs.str();

               my_stack.push(ch);
               temp.clear();
          }
  }
  cout << ch;

}

double Equation::Evaluate(vector <string> &temp){

    string a,b,c;
    a = temp[2]; b = temp[0]; c = temp[1];
    double x,y,z;
    istringstream ins1,ins2;
    ins1.str(a); ins2.str(c);
    ins1 >> x;
    ins2 >> y;

     if(b == "+"){
        z = x + y;
        return z;
     }
     else if(b == "-"){
        z = x - y;
        return z;
     }
     else if(b == "*"){
        z = x * y;
        return z;
     }
     else if(b == "/"){
        z = x / y;
        return z;
     }
     else if(b == "^"){
        z = pow(x,y);
        return z;
     }
     return this;
}

void Equation::reversePolishNotation(){
    string ReversePoli;
    if(CheckValid(Infix)==true){

      string temp;
      temp = Change(Infix);

      Convert(temp, ReversePoli);

      cout << "Reverse Polish Notation:" << endl
      << InsertSpace(ReversePoli);

      string hold;
      hold = InsertSpace(ReversePoli);

      cout << "\n\nResult: ";
      Next(hold);
      cout << "\n\n";
    }
    else{
        cout << "This is an invalid expression.";//change
    }
}

int main(){//this is just to test the inputhandling
    Equation a;
    cout << "Input your expression: " << endl;
    string x;
    cin >> x;
    a.set(x);
    a.reversePolishNotation();
    cin.get();

    return 0;

}
