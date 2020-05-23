#include <iostream>
#include <string>
#define MAX_ELEMENT 100


using namespace std;

typedef struct element {

	string work;
	int precedence;

}Element;

typedef struct heapType {
	Element heap[MAX_ELEMENT];
	int heapSize;
}HeapType;

HeapType* Create()
{
	heapType* temp = new heapType;

	return temp;
}

void Init(HeapType& h)
{
	h.heapSize = 0;
}

// 우선순위수치가 낮아야 가장 우선순위가 높음
void InsertMinHeap(HeapType& h)
{

	Element temp;
	int i = ++(h.heapSize);
	cout << " To do : ";
	getline(cin, temp.work);

	cout << "Precedence :";
	cin >> temp.precedence;
	cin.ignore(32767, '\n');

	if (i != 1) {
		while (temp.precedence < h.heap[i / 2].precedence) // 힙에 원소갯수가 1이 아니고 , 새로 만드는 원소가 부모보다 우선순위수치 가 낮으면 실행
		{
			h.heap[i] = h.heap[i / 2]; // 부모의 위치를  왼쪽 아래로 보낸다.
			i /= 2; // i를 다시 올라간 위치의 부모위치로 지정
		}
	}
	h.heap[i] = temp;

	cout << "Precedence :" << temp.precedence << " , \" " << temp.work << " \" is inserted." << endl;
	return;

}

void DeleteMinHeap(HeapType& h)
{
	int parent, child; //idx값
	Element item, temp;

	item = h.heap[1]; // 첫번째 원소가 가장 우선순위가 높기때문에 리턴값
	temp = h.heap[(h.heapSize--)]; // 힙사이즈를 낮추고 가작 마지막원소값을 temp에 지정

	parent = 1;
	child = 2;

	while (child <= h.heapSize)
	{
		if (child < h.heapSize) // 자식노드의 갯수가 2개
		{
			if (h.heap[child].precedence > h.heap[child + 1].precedence) // 자식노드중 더 우선순위가 높은곳에 child를 위치
				child++;
		}

		if (temp.precedence <= h.heap[child].precedence) break;

		h.heap[parent] = h.heap[child];
		parent = child;
		child *= 2;
	}

	h.heap[parent] = temp;
	
	cout << "To do : " << item.work << endl;
	cout << "Precedence : " << item.precedence << endl;
	cout << "Precedence :" << item.precedence << " , \" " << item.work << " \" is deleted." << endl;

	return;
}

int main()
{

	char c = '\0';
	HeapType* heap = Create();

	Init(*heap);

	while (c != 'q')
	{
		cout << "Menu : Insert(i) , Delete(d) , Quit(q) :";
		cin >> c;
		cin.ignore(32767, '\n');
		cout << "\n =======================" << endl;
		if (c == 'i') InsertMinHeap(*heap);
		else if (c == 'd') DeleteMinHeap(*heap);

		cout << endl;
	}

	cout << "Bye~" << endl;

	system("pause");
	return 0;
}