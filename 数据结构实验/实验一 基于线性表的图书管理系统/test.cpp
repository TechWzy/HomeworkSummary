#include"bookManageSystem.h"

// ��һ��
void test1() {
	Library l;
	l.input();
	l.Dtriger();
	l.display(1);
}

// �ڶ���
void test2() {
	Library l;
	l.input();
	l.priceIncrease();
	l.display(2);	//���ƽ���۸�
}

// ������
void test3() {
	Library l;
	l.input(1);
	l.Triger();
}

// ������
void test4() {
	Library l;
	l.input(1);
	l.Insert();
	l.display(0);
}

// ������
void test5() {
	Library l;
	l.input(1);
	l.Delete();
	l.display(0);
}

int main() {
	test1();
	test1();
	test3();
	test4();
	test5();
	return 0;
}