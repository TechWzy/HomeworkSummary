#include<iostream>
#include<map>
using namespace std;

const int N = 505;
int g[N][N], dis[N], path[N];	//	path[i]��ʾi����ǰ��
bool st[N];
map<char, int>cmap;
map<int, char>imap;
int n, m;

void init() {
	memset(st, false, sizeof st);
	memset(g, 0x3f, sizeof g);
	memset(dis, 0x3f, sizeof dis);
	memset(path, 0, sizeof path);
	cmap.clear();
	imap.clear();
}

//	Dijsktra�㷨
int Dijsktra(int start, int end) {
	dis[start] = 0;	//	��ʼ�����
	path[start] = -1;
	//	��������㵽���������̾�������
	for (int i = 1;i <= n;i++) {
		int j = -1;	//	j�洢������С��
		for (int k = 1;k <= n;k++) {
			if (!st[k] && (j == -1 || dis[k] < dis[j])) {
				j = k;
			}
		}
		st[j] = true;
		//	��������
		for (int p = 1;p <= n;p++) {
			if (dis[p] > dis[j] + g[j][p]) {
				dis[p] = dis[j] + g[j][p];
				path[p] = j;
			}
		}
		if (j == end) {
			return dis[j];
		}
	}
	return dis[end];
}

//	������·��
void getPath(int e) {
	if (e == -1) {
		return;
	}
	getPath(path[e]);
	cout << imap[e] << " ";
}


int main() {
	while (cin >> n >> m && n && m) {
		init();
		
		//	���붥��
		cout << "���붥��:" << endl;
		for (int i = 1;i <= n;i++) {
			char a;
			cin >> a;
			cmap[a] = i;
			imap[i] = a;
		}

		cout << "�����:" << endl;
		//	�����
		for (int i = 1;i <= m;i++) {
			char a, b;
			int d;
			cin >> a >> b >> d;
			g[cmap[a]][cmap[b]] = d;
		}
	
		//	������������
		cout << "����������յ�:" << endl;
		char start, end;
		cin >> start >> end;
		int res = Dijsktra(cmap[start], cmap[end]);
		cout << "res = ";
		cout << res << endl;
		cout << "���·��:";
		getPath(cmap[end]);
		cout << endl;
	}
	return 0;
}