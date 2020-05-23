#include <iostream>

#define MAX_ELEMENT 200

typedef struct treeNode {
	int weight;
	char ch;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode, TREENODE;

typedef struct element {
	TreeNode* pTree;
	char ch;
	int key;
}Element , ELEMENT;

typedef struct heapType {
	Element heap[MAX_ELEMENT];
	int size;
}HeapType, HEAPTYPE;

HeapType* create()
{
	return (new HeapType);
}

void init(HeapType& h)
{
	h.size = 0;
}

void insert_min_heap(HeapType& h, Element item)
{
	int i;
	i = ++(h.size);

	while (i != 1 && item.key < h.heap[i / 2].key)
	{
		h.heap[i] = h.heap[i / 2];
		i /= 2;
	}
	h.heap[i] = item;

	return;
}

Element delete_min_heap(HeapType& h) {
	int parent, child;
	Element item, temp;
	item = h.heap[1];
	temp = h.heap[(h.size)--];
	parent = 1;
	child = 2;
	while (child <= h.size) {
		// 현재 노드의 자식노드중 더 작은 자식노드를 찾는다.
		if ((child < h.size) && (h.heap[child].key) > (h.heap[child + 1].key))
			child++;
		if (temp.key < h.heap[child].key)
			break;
		// 한 단계 아래로 이동
		h.heap[parent] = h.heap[child];
		parent = child;
		child *= 2;
	}
	h.heap[parent] = temp;
	return item;
}

TreeNode* make_tree(TreeNode* left, TreeNode* right)
{
	TreeNode* node = new TreeNode;
	node->left = left;
	node->right = right;

	return node;
}

void destroy_tree(TreeNode& root)
{
	if (&root == NULL)
		return;

	destroy_tree(*root.left);
	destroy_tree(*root.right);
	delete &root;
	return;
}

int is_leaf(TreeNode& root)
{
	return !(root.left) && !(root.right);
}

void print_array(int* codes, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", codes[i]);
	}

	printf("\n");
	return;
}

void print_codes(TreeNode& root, int* codes, int top)
{
	if (root.left)
	{
		codes[top] = 1;
		print_codes(*root.left, codes, top +1);
	}

	if (root.right)
	{
		codes[top] = 0;
		print_codes(*root.right, codes, top +1);
	}

	if (is_leaf(root))
	{
		printf("%c: ", root.ch);
		print_array(codes, top);
	}
}

void huffman_tree(int* freq, char* ch_list, int n)
{
	int i;
	TreeNode * node, *x;
	HeapType* heap;
	Element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(*heap);
	for (i = 0; i < n; i++)
	{
		node = make_tree(NULL, NULL);
		e.ch = node->ch = ch_list[i];
		e.key = node->weight = freq[i];
		e.pTree = node;
		insert_min_heap(*heap, e);

	}
	for (i = 1; i < n; i++) {
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(*heap);
		e2 = delete_min_heap(*heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1.pTree, e2.pTree);
		e.key = x->weight = e1.key + e2.key;
		e.pTree = x;
		printf("%d+%d->%d \n", e1.key, e2.key, e.key);
		insert_min_heap(*heap, e);
	}
	e = delete_min_heap(*heap); // 최종 트리
	print_codes(*e.pTree, codes, top);
	destroy_tree(*e.pTree);
	return;
}

int main(void) {
	char ch_list[] = { 'a', 'b', 'c', 'd', 'e','f','g','h' };
	int freq[] = { 1, 1, 2, 3, 5,8,13,21 };
	huffman_tree(freq, ch_list, 8);
	return 0;
}
