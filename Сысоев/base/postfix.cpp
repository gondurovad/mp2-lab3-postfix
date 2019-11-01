#include <iostream>
#include "postfix.h"
#include "stack.h"
using namespace std;

bool TPostfix::CorrectForm(string st) //проверка корректности введенной формулы
{
string operations = "+-*/";
int len = st.length();
if ((operations.find(st.at(0)) != string::npos) || (operations.find(st.at(len - 1)) != string::npos))
return false;
int open = 0, close = 0; //счетчик откр закр скобок
for (int i = 0; i < len; i++)
{
	if (st.at(i) == '(')
		open++;
	if (st.at(i) == ')')
		close++;
}
if (open != close) return false;
if (st.find("()") != string::npos)
return false;
if ((st.find("++") != string::npos) || (st.find("--") != string::npos) || (st.find("**") != string::npos) || (st.find("//") != string::npos))
return false;
if ((st.find("+-") != string::npos) || (st.find("-+") != string::npos) || (st.find("*/") != string::npos) || (st.find("/*") != string::npos))
return false;
if ((st.find("+*") != string::npos) || (st.find("-*") != string::npos) || (st.find("+/") != string::npos) || (st.find("/+") != string::npos))
return false;
if ((st.find("-/") != string::npos) || (st.find("*+") != string::npos) || (st.find("*-") != string::npos) || (st.find("/-") != string::npos))
return false;
return true;
} /*-----------------------------------------------------------*/

int TPostfix::Priority(char c) //приоритет операций
{
	int res = -1;
	switch (c)
	{
	case '(':
		res = 0;
		break;
	case ')':
		res = 1;
		break;
	case '+':
	case '-':
		res = 2;
		break;
	case '*':
	case '/':
		res = 3;
		break;
	}
	return res;
} /*-----------------------------------------------------------*/

int TPostfix::IsDigit(char c) //проверка на число
{
	int res = 0;
	int a = int(c);
	switch (a)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		res =  1;	
		break;
	}
	return res;
} /*-----------------------------------------------------------*/

int TPostfix::IsOperation(char c) //проверка на операцию
{
	int res = 0;
	switch (c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	{
		res = 1;
		break;
	}
	}
	return res;
} /*-----------------------------------------------------------*/

string TPostfix::ToPostfix() // перевод в постфиксную форму 
{ 
	TStack<char> stack(MaxStackSize);
	int pr; //приоритет текущей операции
	char tmp1, tmp2; //хранение элементов стека и строки
	for (int i = 0; i < infix.length(); i++)
	{
		if (!(IsOperation(infix.at(i)))) //если цифра, в постфикс
		{
			postfix += infix.at(i);
		}
		else //если операция
			if (stack.IsEmpty()) //если стек пуст, кладем операцию
			{
				stack.Push(infix.at(i));
				postfix += ' ';
			}
			else //если стек не пуст, должны сравнить приоритеты
			{
				pr = Priority(infix.at(i));
				if (!pr) //если скобка, кладём в стек
				{
					stack.Push(infix.at(i));
				}
				else //другие операции
				{
					tmp2 = stack.Pop();
					if (pr > Priority(tmp2)) //приоритет текущей больше приоритета предыдущей
					{
						if ((infix.at(i) != ')') || (tmp2 != '('))
						{
							postfix += ' ';
							stack.Push(tmp2);
							stack.Push(infix.at(i));
						}
					}
					else
					{
						if (pr == Priority(tmp2)) //приоритет текущей равен приоритету предыдущей
						{
							postfix += ' ';
							postfix += tmp2;
							stack.Push(infix.at(i));
						}
						else //приоритет текущей меньше приоритета предыдущей
						{
							postfix += ' ';
							postfix += tmp2;
							tmp1 = infix.at(i);
							if (tmp1 == ')') //когда закр скобка, копируем из стека до откр скобки
							{
								do
								{
									tmp2 = stack.Pop();
									if (tmp2 != '(')
									{
										postfix += ' ';
										postfix += tmp2;
									}
								} while (tmp2 != '(');
							}
							else //другие операции
							{
								if (!stack.IsEmpty())
									tmp1 = stack.Pop();
									postfix += tmp1; //предыдущий перемещаем в postfix
									stack.Push(infix.at(i)); //текущий кладем в стек
							}
						}
					}
				}
			}
	}
	while (!stack.IsEmpty()) //переносим все из стека
	{
		postfix += ' ';
		postfix += stack.Pop();
	}
	return postfix;
} /*-----------------------------------------------------------*/

double TPostfix::Calculate(string postfix)
{
	char operation; //операция
	string post;
	double lop, rop; //правй и левый операнды
	double res = 0;
	TStack <double> stack(MaxStackSize);
	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix.at(i) == ' ')
			continue;
		if (!IsOperation(postfix.at(i)))
		{

			while (postfix.at(i) != ' ')
			{
				post += postfix.at(i);
				i++;
			}
			res = stof(post);
			stack.Push(res);
			post.clear();
		}
		else
		{
			if (!(stack.IsEmpty()))
			{
				rop = stack.Pop();
				lop = stack.Pop();
			}
			else throw "error";
			operation = postfix.at(i);
			switch (operation)
			{
			case '+':
			{
				stack.Push(lop + rop);
				break;
			}
			case '-':
			{
				stack.Push(lop - rop);
				break;
			}
			case '*':
			{
				stack.Push(lop * rop);
				break;
			}
			case '/':
			{
				if (rop == 0)
					throw "division by zero";
				else
					stack.Push(lop / rop);
			}
			}
		}

	}
	res = stack.Pop();
	return res;
}
