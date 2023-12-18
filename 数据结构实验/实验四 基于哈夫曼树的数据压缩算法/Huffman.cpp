#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

/*
	注意事项:本实验要求输入字符串的字符种类至少为2种以上,
	且要求字符元素为小写字母...

	关于字符种类为1的情况特例或者更多类型字符的支持在此与予以实现...
*/

// 定义排序结构体
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
HuffmanTree HT;	//	哈夫曼数组指针
int wordArray[N];
string TargetString;	//	待编码的字符串
int n;	//	统计字母个数
string EncodeString;	// 待解码的字符串

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
	// 权重较大的在左边
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

// 每一轮测试都应该删除已有数据
void CreateHuffmanTree(const int& n) {
	int m = 2 * n - 1;
	HT = new HTNode[m + 1];

	for (int i = 1;i <= m;i++) {
		HT[i].lchild = HT[i].rchild = HT[i].parent = 0;
		HT[i].word = '#';
	}

	int pos = 1;

	// 初始化权重与位置
	for (int i = 0;i < N;i++) {
		if (wordArray[i]) {
			HT[pos].weight = wordArray[i];
			HT[pos].word = 'a' + i;
			sNodeCreate(wordArray[i], pos);
			pos++;
		}
	}

	// 选择,合并,删除
	for (int i = n + 1;i <= m;i++) {
		int st1, st2;
		Select(st1, st2);
		HT[st1].parent = HT[st2].parent = i;
		HT[i].lchild = st1, HT[i].rchild = st2;
		HT[i].weight = HT[st1].weight + HT[st2].weight;
		sNodeCreate(HT[i].weight, i);	//	父结点加入到排序队列中...
	}
}

void GetFinalCode(const int& n) {
	// 输出字符出现频次
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
	// 递归退出接口
	if (pos == 0) {
		return;
	}
	if (HT[pos].parent) {
		// 此时的codeString
		codeString += word;
	}

	// 向左子树传递'0',向右子树传递'1'
	HuffmanEncode('0', HT[pos].lchild, codeString);
	HuffmanEncode('1', HT[pos].rchild, codeString);

	// 每一轮都会重新赋值
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
	int strPos = 0;	//	读取string的位置

	string targetString = "";
	while (strPos < strLen) {
		int nextPos = 2 * n - 1;
		while (HT[nextPos].word == '#') {
			// 根据当前的字符判断哈夫曼走向
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
	// 清空排序队列
	while (!st.empty()) {
		sortPtr t = st.back();
		delete t;
		st.pop_back();
	}

	// 删除哈夫曼树
	delete[]HT;

	// 置空字符串
	TargetString = "";
	EncodeString = "";

	// 置空wordArray		
	memset(wordArray, 0, sizeof(wordArray));

	// n置空
	n = 0;
}

void EachOperation() {
	InitData();
	CreateHuffmanTree(n);	//	构建哈夫曼树
	HuffmanEncode('0', 2 * n - 1, "");
	GetFinalCode(n);	//	获取终码
	GetEncodeString(TargetString);
	cout << GetDecodeString() << endl;
	DateClear();	//	清理数据
}

int main() {
	// 主函数
	while (cin >> TargetString && TargetString[0] != '0') {
		EachOperation();
	}
	return 0;
}
