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
	TreeNode *q = p->right; //q는 p의 오른쪽 링크
	// 만약 오른쪽 링크가 NULL이거나 p 노드에 thread가 존재하면, 오른쪽 포인터를 반환
	if (q == NULL || p->right_thread == TRUE)
		return q;
	// 만약 right child가 존재한다면, 다시 가장 왼쪽 노드로 이동
	while (q->left != NULL)
		q = q->left;
	return q;
}
void thread_inorder(TreeNode *t) {
	TreeNode *q;
	q = t;
	while (q->left)
		q = q->left; // 가장 왼쪽 노드로 간다.
		// q의 값이 NULL이 아닌 동안 반복
	do {
		printf("%c ", q->data); // 방문한 노드의 데이터 출력
		q = find_successor(q); // 후속자 함수 호출
	} while (q);
}

int main(void) {
	// leaf node의 right thread (즉, inorder successor) 설정
	n1.right = &n4;
	n2.right = &n3;
	n3.right = &n9;
	n5.right = &n8;
	n6.right = &n7;
	// threaded binary tree에서 중위 순회
	thread_inorder(&n9);
	printf("\n");
	return 0;
}