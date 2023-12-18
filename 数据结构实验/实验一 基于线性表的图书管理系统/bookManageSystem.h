#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;

// ���ͼ������
#define MAXSIZE 1000

// ͼ����Ϣ����
typedef struct {
	char no[20];
	char name[50];
	float price;
}Book;

typedef struct LNode {
	Book data;	//���������
	struct LNode* next;	//����ָ����
}LNode,*LinkList;

// �ඨ��
class Library {
private:
	LinkList head;	//����ͷָ�룬����ָ��Ŀռ�Ϊ��
	static int Number;	//��¼ͼ�������
	static float average;	// ƽ���۸�
	static float supremePrice;	// �鼮����߼۸�
	static int supNumer;	// ��߼۸��鼮�ĸ���
public:
	Library();
	~Library();
	void input();	// �޲���,����һ�����
	void input(int);	// ������
	void display(int);	//ԭ�����
	void priceIncrease();	//��߼۸�
	void GetMostExpensiveBook(LinkList p);
	void Triger();	// GetMostExpensiveBook�Ĵ�����
	void Insert();	// ��������
	void Delete();	// ɾ��ĳһ����
	void DeleteRepeatRecord(LinkList p, char name[50]);	//�ݹ�ķ�ʽɾ���ظ�����
	void Dtriger();
};
