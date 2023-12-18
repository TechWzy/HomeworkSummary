#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;

// 最大图书数量
#define MAXSIZE 1000

// 图书信息定义
typedef struct {
	char no[20];
	char name[50];
	float price;
}Book;

typedef struct LNode {
	Book data;	//结点数据域
	struct LNode* next;	//结点的指针域
}LNode,*LinkList;

// 类定义
class Library {
private:
	LinkList head;	//定义头指针，它不指向的空间为空
	static int Number;	//记录图书的数量
	static float average;	// 平均价格
	static float supremePrice;	// 书籍的最高价格
	static int supNumer;	// 最高价格书籍的个数
public:
	Library();
	~Library();
	void input();	// 无参数,问题一的输出
	void input(int);	// 含参数
	void display(int);	//原本输出
	void priceIncrease();	//提高价格
	void GetMostExpensiveBook(LinkList p);
	void Triger();	// GetMostExpensiveBook的触发器
	void Insert();	// 插入数据
	void Delete();	// 删除某一本书
	void DeleteRepeatRecord(LinkList p, char name[50]);	//递归的方式删除重复数据
	void Dtriger();
};
