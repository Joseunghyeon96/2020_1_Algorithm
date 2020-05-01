#include <iostream>
#include <queue>

using namespace std;

void HotPotato(queue<const char*> players, int num)
{
	if (players.size() < 2)
	{
		cout << "Victory Player is " << players.front() << endl;
		players.pop();
		return;
	}

	int tempNum = num;


	while (tempNum > 0)
	{
		players.push(players.front());
		players.pop();
		tempNum--;
	}

	cout << players.front() << " is out" << endl;
	players.pop();

	HotPotato(players, num);
}

void HotPotato(const char* players[],int playersCount ,int num)
{
	if (playersCount < 2)
	{
		cout << "Victory Player is " << players[0] << endl;
		return;
	}

	int tempNum = num;
	queue<const char*> q;
	for (int i = 0; i < playersCount ; i++)
	{
		q.push(players[i]);
	}

	while (tempNum > 0)
	{
		q.push(q.front());
		q.pop();
		tempNum--;
	}

	cout << q.front() << " is out" << endl;
	q.pop();

	HotPotato(q, num);
}

int main()
{
	const char* players[8] = {"Bill","Brad","Kent","Jane","Susan","David","Messi","Jackson"};

	int num = rand() % 16 + 5;

	HotPotato(players,8, num);

	system("pause");
	return 0;
}