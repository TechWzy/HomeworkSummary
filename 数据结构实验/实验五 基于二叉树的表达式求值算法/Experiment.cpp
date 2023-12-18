#include<iostream>
#include"tool.h"
using namespace std;

#define MaxCap 100

// 二叉树结构
typedef struct Node {
	char data;
	struct Node* lChild;
	struct Node* rchild;
}BiTreeNode,*BiTree;

// 二叉树栈结构
typedef struct BTStack {
	BiTree st[MaxCap];
	int top;
}BTStack;

// 运算符栈结构
typedef struct OPStack {
	char st[MaxCap];
	int top;
}OPStack;

BTStack EXPT;
OPStack OPTR;
BiTree T;	//	二叉树的树根

// 运算符表达式的栈操作
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

// 二叉树栈的表达式栈操作
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




// 以T为根节点创建二叉树
void CreateExpTree(BiTree& T, BiTree lchild, BiTree rchild, const char& ch) {
	T = new BiTreeNode;
	T->data = ch;
	T->lChild = lchild;
	T->rchild = rchild;
}

// 初始化表达式树木
void InitExpTree() {
	InitStack(EXPT);
	InitStack(OPTR);

	// #作为表达式树构建结束标志
	Push(OPTR, '#');

	char ch;
	cin >> ch;
	while (ch != '=' || GetTop(OPTR) != '#') {
		// 如果字符是整型字符
		if (In(ch)) {
			CreateExpTree(T, NULL, NULL, ch);
			Push(EXPT, T);
			cin >> ch;
		}
		else switch (getPriority(GetTop(OPTR),ch))	//判断运算符的优先级
		{
		case '<':
			Push(OPTR, ch);
			cin >> ch;
			break;
		case '>':
			char theta;	//取出运算符
			BiTree a, b;	//	取出二叉树
			Pop(OPTR, theta);
			Pop(EXPT, b);	// 靠右
			Pop(EXPT, a);	// 靠左
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

// 中序遍历二叉树求值,该函数求算以T为根节点的二叉树值
int GetVal(BiTree T) {
	if (In(T->data)) {
		return T->data - '0';	//	递归结束标志
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