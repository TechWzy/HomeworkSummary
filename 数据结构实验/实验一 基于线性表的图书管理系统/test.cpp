#include"bookManageSystem.h"

// 第一问
void test1() {
	Library l;
	l.input();
	l.Dtriger();
	l.display(1);
}

// 第二问
void test2() {
	Library l;
	l.input();
	l.priceIncrease();
	l.display(2);	//输出平均价格
}

// 第三问
void test3() {
	Library l;
	l.input(1);
	l.Triger();
}

// 第四问
void test4() {
	Library l;
	l.input(1);
	l.Insert();
	l.display(0);
}

// 第五问
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