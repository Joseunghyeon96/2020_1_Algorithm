using namespace std;

#include <iostream>
#include <stdio.h>
#include <stack>

bool Palindrome(const char* word) // if word is palindrome , return true
{
	stack<char> stack;
	int i = 0;

	while (word[i] != '\0')
	{
		stack.push(word[i++]);
	}

	char* temp = new char[i];

	for (int j = 0; j < i; j++)
	{
		temp[j] = stack.top();
		stack.pop();
	}

	i = 0;

	while (word[i] != '\0')
	{
		if (word[i] != temp[i])
		{
			delete temp;
			return false;
		}
		i++;
	}
	delete temp;
	return true;
}                                   
int main()
{
	if (Palindrome("abcd"))
	{
		cout << "ȸ���Դϴ�" << endl;
	}
	else
	{
		cout << "ȸ���� �ƴմϴ�." << endl;
	}

	system("pause");
}