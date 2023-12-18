#include"tool.h"

// ��ȡ��������±�����
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

// ��ȡtheta1(ջ��)��theta2֮������ȼ�
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

// �ж��Ƿ�Ϊ�����ַ�
bool In(const char& ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	else {
		return false;
	}
}