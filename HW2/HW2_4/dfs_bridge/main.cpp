#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
typedef struct graphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int visited[MAX_VERTICES];

void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;

	return;
}

void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "Graph: Too many vertices!");
		return;
	}
	g->n++;

	return;
}

void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "Graph: Vertex number error!");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;

	return;
}

// Depth-first search with adjacency matrix (Using Recursion)
void dfs_mat(GraphType* g, int v)
{
	int w;
	visited[v] = TRUE;
	//printf("Vertex %d -> ", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);

	return;
}

int CountBridges(GraphType* g)
{
	int count=0;

	for (int i = 0; i < g->n; i++)
	{
		for (int t = i; t < g->n; t++)
		{
			if (g->adj_mat[i][t])
			{
				int countVisitVertex = 0;
				g->adj_mat[i][t] = 0;
				dfs_mat(g, 0);
				for (int j = 0; j < g->n; j++)
				{
					if (visited[j])
					{
						countVisitVertex++;
						visited[j] = FALSE;
					}
				}

				if (countVisitVertex != (g->n))
				{
					count++;
					printf("\n%d 와 %d 를 연결하는 선은 bridge입니다. \n", i, t);
				}

				g->adj_mat[i][t] = 1;


			}
		}

	}
	return count;
}

int main(void)
{
	GraphType *g;
	g = (GraphType *)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0; i < 10; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 5, 6);
	insert_edge(g, 5, 7);
	insert_edge(g, 6, 7);
	insert_edge(g, 7, 8);
	insert_edge(g, 7, 9);

	printf("The number of bridges is %d. \n",CountBridges(g));
	//printf("dfs : \n");
	//dfs_mat(g, 0);
	//printf("\n");

	free(g);

	return 0;
}