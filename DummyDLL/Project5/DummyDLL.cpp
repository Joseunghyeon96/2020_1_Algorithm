#include <iostream>


typedef struct Node
{
	int data;
	Node *next;
	Node *prev;
}Node;

Node *CreateNode(int data)
{
	Node *temp = new Node;

	if (temp == NULL)
	{
		printf("Node allocation failed!\n");
		exit(1);
	}
	temp->data = data;
	temp->prev = temp->next = NULL;
	return temp;
}

typedef struct List//연결리스트 정의
{
	Node *head;
	Node *tail;
	int count;
}List;

void InitList(List *list)
{
	list->head = CreateNode(0); //dummy head create
	list->tail = CreateNode(0); //dummy tail create
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->count = 0;
}

void InsertNode(List* list, int x)
{
	Node* temp = CreateNode(x);

	temp->prev = list->tail->prev;
	temp->next = list->tail;
	list->tail->prev = temp;
	temp->prev->next = temp;
	list->count++;
}

Node* SearchValue(Node* head, int key)
{
	Node* temp = head->next;
	int i = 1;
	while (temp->next->next != NULL)
	{
		if (temp->data == key) {
			printf("%d번째 노드에서 찾았습니다.\n", i);
			return temp;
		}
		i++;
		temp = temp->next;	
	}

	printf("Do not search %d \n", key);
	exit(1);
}

int main()
{
	List list;
	InitList(&list);

	InsertNode(&list, 1);
	InsertNode(&list, 4);
	InsertNode(&list, 5);
	InsertNode(&list, 7);

	Node* node = SearchValue(list.head, 4);
	printf("%d \n", node->data);

	system("pause");
}