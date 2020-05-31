#include <iostream>

#define INF 1000
#define TRUE 1
#define FALSE 0
#define VERTEXCOUNT 6
struct vlist
{
	int vertex;
	int weight; 
	vlist *link;

};

int* distance;
int* found;
void init(vlist* vertex, int name)
{
	vertex->vertex = name;
	vertex->weight = 0;
	vertex->link = nullptr;
}
void Add(vlist* parentVertex , int name, int weight)
{
	vlist* pLink = parentVertex;

	 while(pLink->link != nullptr) {
		pLink = pLink->link;
	}

	vlist* newVertex = new vlist;
	newVertex->vertex = name;
	newVertex->weight = weight;  // 부모와 name정점간의 가중치
	newVertex->link = nullptr;
	pLink->link = newVertex;
}
void PrintList(vlist* list,int listSize)
{
	for (int i = 0; i < listSize; i++)
	{
		vlist parent = list[i];
		vlist* child = parent.link;
		while (child != nullptr) {
			printf("%d -> %d : %d\n", parent.vertex, child->vertex, child->weight);
			child = child->link;
		}
	}
}
int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void print_status(vlist* list)
{
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < VERTEXCOUNT; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf("        found:    ");
	for (int i = 0; i < VERTEXCOUNT; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

void Dijkstra(vlist* list, int start)
{
	int i, u, w;
	vlist* vertex = &list[start];
	for (i = 0; i < VERTEXCOUNT; i++) 
	{
		found[i] = FALSE;
	}
	while (vertex != nullptr)
	{
		distance[vertex->vertex] = vertex->weight;
		vertex = vertex->link;
	}
	

	// ================  Initialization=============

	found[start] = TRUE;    // Source vertex is visted
	distance[start] = 0;    // Distance of source vertex is zero

	// ================== Start =====================

	for (i = 0; i < VERTEXCOUNT - 1; i++) {
		print_status(list);
		u = choose(distance, VERTEXCOUNT, found);
		found[u] = TRUE;

		vertex = &list[u];
		while (vertex != nullptr)
		{
			if (distance[vertex->vertex] > vertex->weight + distance[u]) // 현재 vertex까지 오는 최저 거리 > 부모부터 자신까지의 거리 +부모까지 오는 최저거리 
				distance[vertex->vertex] = vertex->weight + distance[u];

			vertex = vertex->link;
		}
	}

	print_status(list);
}

void PrintPath(int path[VERTEXCOUNT][VERTEXCOUNT])
{
	for (int i = 0; i < VERTEXCOUNT; i++)
	{
		if (distance[i] == INF)  // 경로가 없는경우 프린트 X
			continue;
		int w = 0;
		printf("%d 까지의 경로 : ", i);
		while (path[i][w] != -1)
		{
			printf("%d -> ", path[i][w]);
			w++;
		}
		printf("\n");
	}
}
void DijkstraPrintPath(vlist* list, int start)
{
	int path[VERTEXCOUNT][VERTEXCOUNT];

	int i, u, w;

	for ( i = 0; i < VERTEXCOUNT; i++)
	{
		for ( u = 0; u < VERTEXCOUNT; u++)
		{
			path[i][u] = -1;
		}
	}
	vlist* vertex = &list[start];
	for (i = 0; i < VERTEXCOUNT; i++)
	{
		found[i] = FALSE; 
		path[i][0] = start;  //모든점으로 오는경로의 시작점을 start로 초기화
	}
	while (vertex != nullptr)
	{
		path[vertex->vertex][1] = vertex->vertex; // 시작점과 연결되있는 점들은 시작->자기자신으로 경로 초기화
		distance[vertex->vertex] = vertex->weight;
		vertex = vertex->link;
	}


	// ================  Initialization=============
	
	found[start] = TRUE;    // Source vertex is visted
	distance[start] = 0;    // Distance of source vertex is zero

	// ================== Start =====================

	for (i = 0; i < VERTEXCOUNT - 1; i++) {
		print_status(list);
		w = 0;
		u = choose(distance, VERTEXCOUNT, found);
		found[u] = TRUE;

		vertex = &list[u];
		while (vertex != nullptr)
		{
			if (distance[vertex->vertex] > vertex->weight + distance[u]) // 현재 vertex까지 오는 최저 거리 > 부모부터 자신까지의 거리 +부모까지 오는 최저거리 
			{
				distance[vertex->vertex] = vertex->weight + distance[u];
				while (path[u][w] != -1) // 부모까지의 경로를 저장
				{
					path[vertex->vertex][w] = path[u][w];
					w++;
				}
				
				path[vertex->vertex][w] = vertex->vertex; // 부모부터 자기자신까지의 경로 추가
			}

			vertex = vertex->link;
		}
	}

	print_status(list);
	PrintPath(path);
}
int main()
{
	vlist* list = new vlist[VERTEXCOUNT];
	distance = new int[VERTEXCOUNT];
	found = new int[VERTEXCOUNT];
	for (int i = 0; i < VERTEXCOUNT; i++)
	{
		init(&list[i], i);
		distance[i] = INF;
	}

	Add(&list[0], 1, 50);
	Add(&list[0], 2, 45);
	Add(&list[0], 3, 10);
	Add(&list[1], 2, 10);
	Add(&list[1], 3, 15);
	Add(&list[2], 4, 30);
	Add(&list[3], 0, 20);
	Add(&list[3], 4, 15);
	Add(&list[4], 1, 20);
	Add(&list[4], 2, 35);
	Add(&list[5], 4, 3);



	//printf("%d %d %d \n", list[0].vertex, list[0].link->vertex, list[0].link->weight);
	DijkstraPrintPath(list, 0);

	delete[] list;
	delete[] distance;
	delete[] found;

	system("pause");
	return 0;
}