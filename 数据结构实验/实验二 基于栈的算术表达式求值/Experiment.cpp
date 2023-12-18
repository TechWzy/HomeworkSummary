#include<iostream>
#include<cstring>
#include <stdlib.h>
using namespace std;

constexpr auto Maxlen = 100;

// 栈OPND
typedef struct OPND{
	double element[Maxlen];
	int top;
}OPND;

// 存储操作元素的栈OPTR
typedef struct OPTR {
	char element[Maxlen];
	int top;
}OPTR;


// 获取运算符的下标索引
int getIndex(char theta) {
	int index = 0;
	switch (theta)
	{
	case '+':
		index = 0;
		break;
	case '-':
		index = 1;
		break;
	case'*':
		index = 2;
		break;
	case '/':
		index = 3;
		break;
	case '(':
		index = 4;
		break;
	case ')':
		index = 5;
		break;
	case '#':
		index = 6;
	default:
		break;
	}
	return index;
}

// 获取theta1(栈顶)与theta2之间的优先级
char getPriority(const char& theta1, const char& theta2) {
	const char priority[][7] = {
		{ '>','>','<','<','<','>','>' },
		{ '>','>','<','<','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '>','>','>','>','<','>','>' },
		{ '<','<','<','<','<','=','0' },
		{ '>','>','>','>','0','>','>' },
		{ '<','<','<','<','<','0','=' },
	};
	int index1 = getIndex(theta1);
	int index2 = getIndex(theta2);
	return priority[index1][index2];
}

// 栈的初始化
void stackInit(OPND& st1,OPTR& st2) {
	st1.top = 0;
	st2.top = 1;
	st2.element[0] = '#';
}

// 出栈
double elePop(OPND& st) {
	int top = --st.top;
	return st.element[top];
}
char elePop(OPTR& st) {
	int top = --st.top;
	return st.element[top];
}

// 入栈
void elePush(OPND& st,const double& ele) {
	st.element[st.top++] = ele;
}
void elePush(OPTR& st, const char& ele) {
	st.element[st.top++] = ele;
}

// 取出栈顶元素
double getTop(OPND& st) {
	int top = st.top - 1;
	return st.element[top];
}
char getTop(OPTR& st) {
	int top = st.top - 1;
	return st.element[top];
}

// 计算
double Calculate(const double& num1, const double& num2, const char& theta) {
	switch (theta)
	{
	case'+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	default:
		return 0;
	}
}

void StackCalculation(const char str[]) {
	OPND st1;
	OPTR st2;
	stackInit(st1, st2);

	int pos = 0;	// 记录读取字符串的位置

	while (st2.top) {
		// 判断是否为数字字符串
		if (str[pos] >= '0' && str[pos] <= '9') {
			int t = 0;
			char numStr[Maxlen];
			while (str[pos] >= '0' && str[pos] <= '9' || str[pos] == '.') {
				numStr[t] = str[pos];
				pos++;
				t++;
			}
			numStr[t] = '\0';
			double res = atof(numStr);
			elePush(st1, res);
		}
		else {
			// 当str[pos]为操作字符
			char theta = str[pos++];
			if (theta == '=') {
				theta = '#';
			}

			while (true) {
				char top = getTop(st2);
				char cmp = getPriority(top, theta);
				if (cmp == '>') {
					// 执行计算操作
					double num2 = elePop(st1);
					double num1 = elePop(st1);
					char op = elePop(st2);
					double res = Calculate(num1, num2, op);
					elePush(st1, res);
				}
				else if (cmp == '=') {
					elePop(st2);
					break;
				}
				else {
					elePush(st2, theta);
					break;
				}
			}
		}
	}
	cout << st1.element[0] << endl;
}


int main() {
	char str[Maxlen];
	while (cin >> str && str[0] != '=') {
		StackCalculation(str);
	}
	return 0;
}