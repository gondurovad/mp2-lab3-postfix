#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	int Priority(char c);
	int IsDigit(char c);
	int IsOperation(char c);
public:

	TPostfix(string _infix = "1+1")
	{
		if (!CorrectForm(_infix)) throw "error";
		infix = _infix;
	}
	string GetInfix() { return infix; }
	bool CorrectForm (string st); //проверка корректности введенной формулы
	string GetPostfix() { return postfix; }
	string ToPostfix();   //перевод в постфиксную форму
	double Calculate(string postfix); //вычисление по постфиксной форме
};

#endif