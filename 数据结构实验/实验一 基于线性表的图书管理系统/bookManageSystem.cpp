#include"bookManageSystem.h"


// 构造函数
Library::Library() {
	this->head = new LNode;
	head->next = NULL;
	// cout << "初始化成功" << endl;
}

int Library::Number = 0;
float Library::average = 0;
float Library::supremePrice = 0;
int Library::supNumer = 0;

void Library::input() {
	cout << "输入案例" << endl;
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
	cout << "输入案例" << endl;
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

// 输出案例
void Library::display(int choice) {
	cout << "输出案例" << endl;
	if (choice == 1) {
		cout << this->Number << endl;
	}
	else if (choice == 2) {
		printf("%.2f\n", this->average);
	}
	LinkList p = this->head->next;
	// 遍历链表
	while (p) {
		printf("%s %s %.2f\n", p->data.no, p->data.name, p->data.price);
		p = p->next;
	}
}

// 提高价格
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

// 查询最高价格
void Library::GetMostExpensiveBook(LinkList p) {
	if (p == NULL) {
		cout << this->supNumer << endl;	// 输出最高价格书籍的个数
		return;
	}
	if (p->data.price > this->supremePrice) {
		// 更新最高价格与书籍数量
		this->supremePrice = p->data.price;
		this->supNumer = 1;
	}
	else if (p->data.price == this->supremePrice) {
		this->supNumer++;
	}
	// 不允许出现p = p->next,Func(p)
	Library::GetMostExpensiveBook(p->next);
	// 判断该书籍是否最高价格的书籍
	if (p->data.price == this->supremePrice) {
		printf("%s %s %.2f\n", p->data.no, p->data.name, p->data.price);
	}
}

// 由于main环境无法访问私有变量head,需要构建一个触发器，对GetMostExpensiveBook传参
void Library::Triger() {
	cout << "输出案例" << endl;
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
	// 允许插在表尾巴
	if (pos <= 0 || pos >= this->Number + 2) {
		cout << "抱歉， 入库位置非法!" << endl;
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

// 书籍出库
void Library::Delete() {
	int pos = 0;
	cin >> pos;
	if (pos <= 0 || pos >= this->Number + 1) {
		cout << "抱歉， 出库位置非法!" << endl;
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

// 书籍去重
void Library::DeleteRepeatRecord(LinkList p, char IBSN[20]) {
	// 当输入的指针为空时，结束第一轮的递归操作
	if (p == NULL) {
		return;
	}
	
	// 如果IBSN为空，那么说明此次操作是新一轮递归的开端,
	// 需删除与p结点有相同IBSN的其他结点
	int len = strlen(IBSN);
	if (len == 0) {
		// IBSN复制p结点的IBSN
		strcpy(IBSN, p->data.no);
	}

	// 删除与p相连且与p有相同IBSN值的结点
	while (p->next) {
		int res = strcmp(IBSN, p->next->data.no);

		// 当p->next的IBSN值与p结点相同时，删除p->next所指向的结点
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

	// 删除不与p相连但与p有相同IBSN值的结点
	Library::DeleteRepeatRecord(p->next, IBSN);

	// 如果下一个结点依旧不为空，那么继续执行排重操作
	if (p->next) {
		// 执行下一轮排重操作时，先把IBSN值置空
		len = strlen(IBSN);
		memset(IBSN, 0, len);
		Library::DeleteRepeatRecord(p->next, IBSN);
	}
}

// 去重触发器
void Library::Dtriger() {
	char IBSN[20] = "";
	this->DeleteRepeatRecord(this->head->next, IBSN);
}