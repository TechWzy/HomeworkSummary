#include"bookManageSystem.h"


// ���캯��
Library::Library() {
	this->head = new LNode;
	head->next = NULL;
	// cout << "��ʼ���ɹ�" << endl;
}

int Library::Number = 0;
float Library::average = 0;
float Library::supremePrice = 0;
int Library::supNumer = 0;

void Library::input() {
	cout << "���밸��" << endl;
	float sum = 0;
	LinkList p = this->head;
	while (true) {
		LinkList newPtr = new LNode;
		cin >> newPtr->data.no >> newPtr->data.name >> newPtr->data.price;
		if (newPtr->data.no[0] == '0' && newPtr->data.name[0] == '0' && newPtr->data.price == 0) {
			delete newPtr;
			newPtr = NULL;
			this->average = sum / this->Number;
			break;
		}
		else {
			sum += newPtr->data.price;
			newPtr->next = NULL;
			p->next = newPtr;
			p = newPtr;
			this->Number++;
		}
	}
}

void Library::input(int choice) {
	cout << "���밸��" << endl;
	int bookNum = 0;
	cin >> bookNum;
	LinkList p = this->head;
	while (true) {
		LinkList newPtr = new LNode;
		if (!bookNum) {
			delete newPtr;
			newPtr = NULL;
			break;
		}
		else {
			cin >> newPtr->data.no >> newPtr->data.name >> newPtr->data.price;
			newPtr->next = NULL;
			p->next = newPtr;
			p = newPtr;
			this->Number++;
		}
		bookNum--;
	}
}

// �������
void Library::display(int choice) {
	cout << "�������" << endl;
	if (choice == 1) {
		cout << this->Number << endl;
	}
	else if (choice == 2) {
		printf("%.2f\n", this->average);
	}
	LinkList p = this->head->next;
	// ��������
	while (p) {
		printf("%s %s %.2f\n", p->data.no, p->data.name, p->data.price);
		p = p->next;
	}
}

// ��߼۸�
void Library::priceIncrease() {
	float sta = this->average;
	float ratio = 0.1;
	LinkList p = this->head->next;
	while (p) {
		if (p->data.price < sta) {
			p->data.price *= 1.2;
		}
		else {
			p->data.price *= 1.1;
		}
		p = p->next;
	}
}

// ��ѯ��߼۸�
void Library::GetMostExpensiveBook(LinkList p) {
	if (p == NULL) {
		cout << this->supNumer << endl;	// �����߼۸��鼮�ĸ���
		return;
	}
	if (p->data.price > this->supremePrice) {
		// ������߼۸����鼮����
		this->supremePrice = p->data.price;
		this->supNumer = 1;
	}
	else if (p->data.price == this->supremePrice) {
		this->supNumer++;
	}
	// ���������p = p->next,Func(p)
	Library::GetMostExpensiveBook(p->next);
	// �жϸ��鼮�Ƿ���߼۸���鼮
	if (p->data.price == this->supremePrice) {
		printf("%s %s %.2f\n", p->data.no, p->data.name, p->data.price);
	}
}

// ����main�����޷�����˽�б���head,��Ҫ����һ������������GetMostExpensiveBook����
void Library::Triger() {
	cout << "�������" << endl;
	this->GetMostExpensiveBook(this->head->next);
}

Library::~Library() {
	LinkList p = this->head;
	while (p) {
		LinkList tmp = p->next;
		delete p;
		p = tmp;
	}
}

void Library::Insert() {
	int pos = 0;
	cin >> pos;
	// ������ڱ�β��
	if (pos <= 0 || pos >= this->Number + 2) {
		cout << "��Ǹ�� ���λ�÷Ƿ�!" << endl;
		return;
	}
	LinkList p = this->head;
	LinkList newPtr = new LNode;
	cin >> newPtr->data.no >> newPtr->data.name >> newPtr->data.price;
	newPtr->next = NULL;
	while (--pos) {
		p = p->next;
	}
	newPtr->next = p->next;
	p->next = newPtr;
	this->Number++;
}

// �鼮����
void Library::Delete() {
	int pos = 0;
	cin >> pos;
	if (pos <= 0 || pos >= this->Number + 1) {
		cout << "��Ǹ�� ����λ�÷Ƿ�!" << endl;
		return;
	}

	LinkList p = this->head;
	while (--pos) {
		p = p->next;
	}
	LinkList tmp = p->next;
	p->next = tmp->next;
	this->Number--;
	delete tmp;
	tmp = NULL;
}

// �鼮ȥ��
void Library::DeleteRepeatRecord(LinkList p, char IBSN[20]) {
	// �������ָ��Ϊ��ʱ��������һ�ֵĵݹ����
	if (p == NULL) {
		return;
	}
	
	// ���IBSNΪ�գ���ô˵���˴β�������һ�ֵݹ�Ŀ���,
	// ��ɾ����p�������ͬIBSN���������
	int len = strlen(IBSN);
	if (len == 0) {
		// IBSN����p����IBSN
		strcpy(IBSN, p->data.no);
	}

	// ɾ����p��������p����ͬIBSNֵ�Ľ��
	while (p->next) {
		int res = strcmp(IBSN, p->next->data.no);

		// ��p->next��IBSNֵ��p�����ͬʱ��ɾ��p->next��ָ��Ľ��
		if (!res) {
			LinkList tmp = p->next;
			p->next = tmp->next;
			delete tmp;
			tmp = NULL;
			this->Number--;
		}
		else {
			break;
		}
	}

	// ɾ������p��������p����ͬIBSNֵ�Ľ��
	Library::DeleteRepeatRecord(p->next, IBSN);

	// �����һ��������ɲ�Ϊ�գ���ô����ִ�����ز���
	if (p->next) {
		// ִ����һ�����ز���ʱ���Ȱ�IBSNֵ�ÿ�
		len = strlen(IBSN);
		memset(IBSN, 0, len);
		Library::DeleteRepeatRecord(p->next, IBSN);
	}
}

// ȥ�ش�����
void Library::Dtriger() {
	char IBSN[20] = "";
	this->DeleteRepeatRecord(this->head->next, IBSN);
}