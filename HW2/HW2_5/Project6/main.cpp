#include <iostream>

#define TRUE 1
#define FALSE 0
typedef struct treeNode {
	int data;
	struct treeNode *left, *right;
	int right_thread; // TRUE if there is a right thread
} TreeNode;
// G
// C F
// A B D E
TreeNode n1 = { 'D', NULL, NULL, 1 };
TreeNode n2 = { 'H', NULL, NULL, 1 };
TreeNode n3 = { 'E', &n2, NULL, 1 };
TreeNode n4 = { 'B', &n1, &n3, 0 };
TreeNode n5 = { 'F', NULL, NULL, 1 };
TreeNode n6 = { 'I', NULL, NULL, 1 };
TreeNode n7 = { 'G', &n6, NULL, 0 };
TreeNode n8 = { 'C', &n5, &n7, 0 };
TreeNode n9 = { 'A', &n4, &n8, 0 };
//TreeNode *exp = &n9;

TreeNode *find_successor(TreeNode *p) {
	TreeNode *q = p->right; //q�� p�� ������ ��ũ
	// ���� ������ ��ũ�� NULL�̰ų� p ��忡 thread�� �����ϸ�, ������ �����͸� ��ȯ
	if (q == NULL || p->right_thread == TRUE)
		return q;
	// ���� right child�� �����Ѵٸ�, �ٽ� ���� ���� ���� �̵�
	while (q->left != NULL)
		q = q->left;
	return q;
}
void thread_inorder(TreeNode *t) {
	TreeNode *q;
	q = t;
	while (q->left)
		q = q->left; // ���� ���� ���� ����.
		// q�� ���� NULL�� �ƴ� ���� �ݺ�
	do {
		printf("%c ", q->data); // �湮�� ����� ������ ���
		q = find_successor(q); // �ļ��� �Լ� ȣ��
	} while (q);
}

int main(void) {
	// leaf node�� right thread (��, inorder successor) ����
	n1.right = &n4;
	n2.right = &n3;
	n3.right = &n9;
	n5.right = &n8;
	n6.right = &n7;
	// threaded binary tree���� ���� ��ȸ
	thread_inorder(&n9);
	printf("\n");
	return 0;
}