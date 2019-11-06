#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string form;
	double res;
	cout << "Enter form: ";
	getline(cin, form);
	TPostfix postfix(form);
	if (postfix.CorrectForm(form))
	{
		cout << "Form: " << postfix.GetInfix() << endl;
		cout << "Postfix form: " << postfix.ToPostfix() << endl;
		cout << postfix.Calculate(postfix.ToPostfix()) << endl;
	}
	else
		cout << "Brackets error!" << endl;
}
