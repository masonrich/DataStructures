// Copyright 2019, Bradley Peterson, Weber State University, all rights reserved. (4/2019)

#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cmath>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#else
#include <stdio.h>
#endif

using std::stack;
using std::istringstream;
using std::ostringstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pow;

struct Node {
public:
    string data{};
    Node* llink{ nullptr };
    Node* rlink{ nullptr };
};

class TreeParser{

private:
    stack<string> mathStack;
    double castStrToDouble(string const &s);
    string castDoubleToStr(const double d);
    void initialize();
    bool isDigit(char c);
    bool isOperator(char c);
    void inorderTraversal(Node* ptr) const;
    void postorderTraversal(Node* ptr) const;
    void processExpression (Node* p);
    void computeAnswer(Node* p);
    Node* root{ nullptr };

protected:
    string expression;
    int position;  //index referring to which character of the string you are on.

public:
    TreeParser();
    void displayParseTree();
    void processExpression(string &expression);
    string computeAnswer();
    void inorderTraversal() const;
    void postorderTraversal() const;
};

////////////// MY METHODS ////////////////

void TreeParser::inorderTraversal() const {
    inorderTraversal(root);
    cout << endl;
}

void TreeParser::inorderTraversal(Node* ptr) const {
    if (ptr) {
        inorderTraversal(ptr->llink);
        cout << ptr->data << " ";
        inorderTraversal(ptr->rlink);
    }
}

void TreeParser::postorderTraversal() const {
    postorderTraversal(root);
    cout << endl;
}

void TreeParser::postorderTraversal(Node* ptr) const {
    if (ptr) {
        postorderTraversal(ptr->llink);
        postorderTraversal(ptr->rlink);
        cout << ptr->data << " ";
    }
}

bool TreeParser::isDigit(char c) {
    if(c >= '0' && c <= '9'){
        return true;
    }
    return false;
}

bool TreeParser::isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^'){
        return true;
    }
    return false;
}

void TreeParser::processExpression(string &expression) {
    if (expression == ""){
        return;
    }
    else{
        this->expression = expression;
        this->position = 0;
        Node* temp = new Node();
        this->root = temp;
        processExpression(this->root);
    }
}

void TreeParser::processExpression(Node *p) {
    while(position < expression.length()){
            if(expression[position] == '('){
                Node* temp = new Node();
                temp->llink = nullptr;
                temp->rlink = nullptr;
                p->llink = temp;
                position++;
                processExpression(p->llink); //recursively go left
            }
            else if(isDigit(expression[position])){
                string tempString = "";
                do {
                    tempString += expression[position];
                    position++;
                } while(isDigit(expression[position]));
                p->data = tempString; //store the temp string in the node
                return;
            }
            else if(isOperator(expression[position])){
                p->data = expression[position];
                Node* temp = new Node();
                temp->llink = nullptr;
                temp->rlink = nullptr;
                p->rlink = temp;
                position++;
                processExpression(p->rlink); //recursively go right
            }
            else if(expression[position] == ')'){
                position++;
                return;
            }
            else if(expression[position] == ' '){
                position++;
            }
    }
}

string TreeParser::computeAnswer() {
    computeAnswer(this->root);
    return mathStack.top();
}

void TreeParser::computeAnswer(Node* p) {
    if(p){
        computeAnswer(p->llink);
        computeAnswer(p->rlink);

        if(isDigit(p->data[0])){
            mathStack.push(p->data);
        }

        else if (isOperator(p->data[0])){
            string a = mathStack.top();
            mathStack.pop();
            string b = mathStack.top();
            mathStack.pop();
            castStrToDouble(a);
            castStrToDouble(b);
            switch(p->data[0])
            {
                case '+':
                    mathStack.push(castDoubleToStr(castStrToDouble(b)+castStrToDouble(a)));
                    break;
                case '-':
                    mathStack.push(castDoubleToStr(castStrToDouble(b)-castStrToDouble(a)));
                    break;
                case '*':
                    mathStack.push(castDoubleToStr(castStrToDouble(b)*castStrToDouble(a)));
                    break;
                case '/':
                    mathStack.push(castDoubleToStr(castStrToDouble(b)/castStrToDouble(a)));
                    break;
                case '^':
                    mathStack.push(castDoubleToStr(pow(castStrToDouble(b),castStrToDouble(a))));
                    return;
                default:
                    cout << "error calculating numbers" << endl;
            }

        }

    }
}
/////////////////////////////////////////

void TreeParser::initialize() {
    expression = "";
    position = 0;
    while (!mathStack.empty()) {
        mathStack.pop();
    }
}

double TreeParser::castStrToDouble(const string &s) {
    istringstream iss(s);
    double x;
    iss >> x;
    return x;
}

string TreeParser::castDoubleToStr(const double d) {
    ostringstream oss;
    oss << d;
    return oss.str();

}

TreeParser::TreeParser() {
    initialize();
}

void TreeParser::displayParseTree() {
    cout << "The expression seen using in-order traversal: ";
    inorderTraversal();
    cout << "The expression seen using post-order traversal: ";
    postorderTraversal();
    cout << endl;

}

void pressAnyKeyToContinue() {
    printf("Press any key to continue\n");

    //Linux and Mac users with g++ don't need this
    //But everyone else will see this message.
#ifndef __GNUC__
    _getch();
#else
    int c;
	fflush(stdout);
	do c = getchar(); while ((c != '\n') && (c != EOF));
#endif

}

// Copyright 2019, Bradley Peterson, Weber State University, all rights reserved. (4/2019)

int main() {

    TreeParser *tp = new TreeParser;

    string expression = "(4+7)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 11 as a double output
    cout << endl;

    expression = "(7-4)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 3 as a double output
    cout << endl;

    expression = "(9*5)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 45 as a double output
    cout << endl;

    expression = "(4^3)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 64 as a double output
    cout << endl;

    expression = "((2-5)-5)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display -8 as a double output
    cout << endl;

    expression = "(5*(6/2))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 15 as a double output
    cout << endl;

    expression = "((1 + 2) * (3 + 4))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 21 as a double output
    cout << endl;

    expression = "(543+321)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 864 as a double output
    cout << endl;

    expression = "((5*(3+2))+(7*(4+6)))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display 95 as a double output
    cout << endl;

    expression = "(((((3+12)-7)*120)/(2+3))^3)";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 7077888 as a double output
    cout << endl;//NOTE, it won't be exact, it will display as scientific notation!

    expression = "(((((9+(2*(110-(30/2))))*8)+1000)/2)+(((3^4)+1)/2))";
    tp->processExpression(expression);
    tp->displayParseTree();
    cout << "The result is: " << tp->computeAnswer() << endl; //Should display close to 1337 as a double/decimal output
    cout << endl;

    pressAnyKeyToContinue();
    return 0;
}
