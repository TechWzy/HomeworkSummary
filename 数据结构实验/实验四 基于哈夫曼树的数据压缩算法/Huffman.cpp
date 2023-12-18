#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

/*
	ע������:��ʵ��Ҫ�������ַ������ַ���������Ϊ2������,
	��Ҫ���ַ�Ԫ��ΪСд��ĸ...

	�����ַ�����Ϊ1������������߸��������ַ���֧���ڴ�������ʵ��...
*/

// ��������ṹ��
typedef struct {
	int weight;
	int pos;
}sortNode,*sortPtr;

// haffmanTree
typedef struct {
	char word;
	int weight;
	int lchild, rchild, parent;
}HTNode,*HuffmanTree;

const int N = 26;
vector<sortPtr> st;
map<char, string> wordMap;
HuffmanTree HT;	//	����������ָ��
int wordArray[N];
string TargetString;	//	��������ַ���
int n;	//	ͳ����ĸ����
string EncodeString;	// ��������ַ���

bool cmp(const sortPtr& s1, const sortPtr& s2) {
	return s1->weight > s2->weight;
}

void sNodeCreate(const int& weight, const int& pos) {
	sortPtr t = new sortNode;
	t->pos = pos;
	t->weight = weight;
	st.push_back(t);
}

void Select(int& st1, int& st2) {
	// Ȩ�ؽϴ�������
	sortPtr t;
	sort(st.begin(), st.end(), cmp);
	t = st.back();
	st2 = t->pos;
	delete t;
	st.pop_back();
	t = st.back();
	st1 = t->pos;
	st.pop_back();
	delete t;
}

void InitData() {
	int strLen = TargetString.length();

	for (int i = 0;i < strLen;i++) {
		wordArray[TargetString[i] - 'a']++;
	}

	for (int i = 0;i < N;i++) {
		if (wordArray[i]) {
			n++;
		}
	}
}

// ÿһ�ֲ��Զ�Ӧ��ɾ����������
void CreateHuffmanTree(const int& n) {
	int m = 2 * n - 1;
	HT = new HTNode[m + 1];

	for (int i = 1;i <= m;i++) {
		HT[i].lchild = HT[i].rchild = HT[i].parent = 0;
		HT[i].word = '#';
	}

	int pos = 1;

	// ��ʼ��Ȩ����λ��
	for (int i = 0;i < N;i++) {
		if (wordArray[i]) {
			HT[pos].weight = wordArray[i];
			HT[pos].word = 'a' + i;
			sNodeCreate(wordArray[i], pos);
			pos++;
		}
	}

	// ѡ��,�ϲ�,ɾ��
	for (int i = n + 1;i <= m;i++) {
		int st1, st2;
		Select(st1, st2);
		HT[st1].parent = HT[st2].parent = i;
		HT[i].lchild = st1, HT[i].rchild = st2;
		HT[i].weight = HT[st1].weight + HT[st2].weight;
		sNodeCreate(HT[i].weight, i);	//	�������뵽���������...
	}
}

void GetFinalCode(const int& n) {
	// ����ַ�����Ƶ��
	for (int i = 0;i < N;i++) {
		if (wordArray[i]) {
			char word = 'a' + i;
			cout << word << ":" << wordArray[i] << " ";
		}
	}
	cout << endl;

	for (int i = 1;i <= 2 * n - 1;i++) {
		cout << i << " " << HT[i].weight << " " << HT[i].parent << " " << HT[i].lchild
			<< " " << HT[i].rchild << endl;
	}

	for (int i = 0;i < N;i++) {
		if (wordArray[i]) {
			char word = 'a' + i;
			cout << word << ":" << wordMap[word] << " ";
		}
	}
	cout << endl;
}

void HuffmanEncode(char word,int pos,string codeString) {
	// �ݹ��˳��ӿ�
	if (pos == 0) {
		return;
	}
	if (HT[pos].parent) {
		// ��ʱ��codeString
		codeString += word;
	}

	// ������������'0',������������'1'
	HuffmanEncode('0', HT[pos].lchild, codeString);
	HuffmanEncode('1', HT[pos].rchild, codeString);

	// ÿһ�ֶ������¸�ֵ
	if (HT[pos].word != '#') {
		wordMap[HT[pos].word] = codeString;
	}
}

void GetEncodeString(string TargetString) {
	int strlen = TargetString.length();

	for (int i = 0;i < strlen;i++) {
		cout << wordMap[TargetString[i]];
		EncodeString += wordMap[TargetString[i]];
		
	}
	cout << endl;
}

string GetDecodeString() {	
	int strLen = EncodeString.length();
	int strPos = 0;	//	��ȡstring��λ��

	string targetString = "";
	while (strPos < strLen) {
		int nextPos = 2 * n - 1;
		while (HT[nextPos].word == '#') {
			// ���ݵ�ǰ���ַ��жϹ���������
			if (EncodeString[strPos] == '0') {
				nextPos = HT[nextPos].lchild;
			}
			else {
				nextPos = HT[nextPos].rchild;
			}
			strPos++;
		}
		targetString += HT[nextPos].word;
	}
	return targetString;
}

void DateClear() {
	// ����������
	while (!st.empty()) {
		sortPtr t = st.back();
		delete t;
		st.pop_back();
	}

	// ɾ����������
	delete[]HT;

	// �ÿ��ַ���
	TargetString = "";
	EncodeString = "";

	// �ÿ�wordArray		
	memset(wordArray, 0, sizeof(wordArray));

	// n�ÿ�
	n = 0;
}

void EachOperation() {
	InitData();
	CreateHuffmanTree(n);	//	������������
	HuffmanEncode('0', 2 * n - 1, "");
	GetFinalCode(n);	//	��ȡ����
	GetEncodeString(TargetString);
	cout << GetDecodeString() << endl;
	DateClear();	//	��������
}

int main() {
	// ������
	while (cin >> TargetString && TargetString[0] != '0') {
		EachOperation();
	}
	return 0;
}
