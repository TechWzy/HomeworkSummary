#include<iostream>
#include"tool.h"
using namespace std;

#define MaxCap 100

// �������ṹ
typedef struct Node {
	char data;
	struct Node* lChild;
	struct Node* rchild;
}BiTreeNode,*BiTree;

// ������ջ�ṹ
typedef struct BTStack {
	BiTree st[MaxCap];
	int top;
}BTStack;

// �����ջ�ṹ
typedef struct OPStack {
	char st[MaxCap];
	int top;
}OPStack;

BTStack EXPT;
OPStack OPTR;
BiTree T;	//	������������

// ��������ʽ��ջ����
void InitStack(OPStack& s) {
	s.top = 0;
}

void Push(OPStack& OPTR, const char& ch) {
	OPTR.st[OPTR.top++] = ch;
}

char GetTop(const OPStack& OPTR) {
	return OPTR.st[OPTR.top - 1];
}

void Pop(OPStack& OPTR, char& theta) {
	theta = OPTR.st[--OPTR.top];
}

// ������ջ�ı��ʽջ����
void InitStack(BTStack& s) {
	s.top = 0;
}

void Push(BTStack& EXPT, const BiTree& BTree) {
	EXPT.st[EXPT.top++] = BTree;
}

void Pop(BTStack& EXPT, BiTree& BTree) {
	BTree = EXPT.st[--EXPT.top];
}

BiTree GetTop(BTStack& EXPT) {
	return EXPT.st[EXPT.top - 1];
}




// ��TΪ���ڵ㴴��������
void CreateExpTree(BiTree& T, BiTree lchild, BiTree rchild, const char& ch) {
	T = new BiTreeNode;
	T->data = ch;
	T->lChild = lchild;
	T->rchild = rchild;
}

// ��ʼ�����ʽ��ľ
void InitExpTree() {
	InitStack(EXPT);
	InitStack(OPTR);

	// #��Ϊ���ʽ������������־
	Push(OPTR, '#');

	char ch;
	cin >> ch;
	while (ch != '=' || GetTop(OPTR) != '#') {
		// ����ַ��������ַ�
		if (In(ch)) {
			CreateExpTree(T, NULL, NULL, ch);
			Push(EXPT, T);
			cin >> ch;
		}
		else switch (getPriority(GetTop(OPTR),ch))	//�ж�����������ȼ�
		{
		case '<':
			Push(OPTR, ch);
			cin >> ch;
			break;
		case '>':
			char theta;	//ȡ�������
			BiTree a, b;	//	ȡ��������
			Pop(OPTR, theta);
			Pop(EXPT, b);	// ����
			Pop(EXPT, a);	// ����
			CreateExpTree(T, a, b, theta);
			Push(EXPT, T);
			break;
		case '=':
			char x;
			Pop(OPTR, x);
			cin >> ch;
			break;
		default:
			break;
		}
	}
}

int Calculate(int t1, int t2, char theta) {
	if (theta == '+') {
		return t1 + t2;
	}
	else if (theta == '-') {
		return t1 - t2;
	}
	else if (theta == '*') {
		return t1 * t2;
	}
	else if (theta == '/') {
		return t1 / t2;
	}
	else {
		return 0;
	}
}

// ���������������ֵ,�ú���������TΪ���ڵ�Ķ�����ֵ
int GetVal(BiTree T) {
	if (In(T->data)) {
		return T->data - '0';	//	�ݹ������־
	}
	else {
		char op = T->data;
		int t1 = GetVal(T->lChild);
		int t2 = GetVal(T->rchild);
		return Calculate(t1, t2, op);
	}
}

int main() {
	InitExpTree();
	int res = GetVal(GetTop(EXPT));
	cout << "res = " << res << endl;
	return 0;
}