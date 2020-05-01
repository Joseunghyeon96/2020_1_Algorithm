#include <iostream>
#include <deque>

using namespace std;

bool CheckPalindrome(const char* word)
{
	deque<char> dq1;
	deque<char> dq2;

	for (int i = 0; i < strlen(word); i++)
	{
		dq1.push_back(word[i]);
	}

	for (int i = 0; i < strlen(word); i++)
	{
		dq2.push_front(word[i]);
	}


	for (int i = 0; i < dq1.size(); i++)
	{
		if (dq1.at(i) != dq2.at(i))
			return false;
	}


	return true;
}
void main()
{
	const char* word = "abcdr";

	if (CheckPalindrome(word))
		printf(" 회문 입니다 . \n");

	else
		printf(" 회문 아닙니다. \n");

	system("pause");
}