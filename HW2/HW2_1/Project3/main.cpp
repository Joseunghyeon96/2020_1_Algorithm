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

// �켱������ġ�� ���ƾ� ���� �켱������ ����
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
		while (temp.precedence < h.heap[i / 2].precedence) // ���� ���Ұ����� 1�� �ƴϰ� , ���� ����� ���Ұ� �θ𺸴� �켱������ġ �� ������ ����
		{
			h.heap[i] = h.heap[i / 2]; // �θ��� ��ġ��  ���� �Ʒ��� ������.
			i /= 2; // i�� �ٽ� �ö� ��ġ�� �θ���ġ�� ����
		}
	}
	h.heap[i] = temp;

	cout << "Precedence :" << temp.precedence << " , \" " << temp.work << " \" is inserted." << endl;
	return;

}

void DeleteMinHeap(HeapType& h)
{
	int parent, child; //idx��
	Element item, temp;

	item = h.heap[1]; // ù��° ���Ұ� ���� �켱������ ���⶧���� ���ϰ�
	temp = h.heap[(h.heapSize--)]; // ������� ���߰� ���� ���������Ұ��� temp�� ����

	parent = 1;
	child = 2;

	while (child <= h.heapSize)
	{
		if (child < h.heapSize) // �ڽĳ���� ������ 2��
		{
			if (h.heap[child].precedence > h.heap[child + 1].precedence) // �ڽĳ���� �� �켱������ �������� child�� ��ġ
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