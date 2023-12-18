#include<iostream>
#include<map>
using namespace std;

const int N = 505;
int g[N][N], dis[N], path[N];	//	path[i]表示i结点的前驱
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

//	Dijsktra算法
int Dijsktra(int start, int end) {
	dis[start] = 0;	//	初始化起点
	path[start] = -1;
	//	构建从起点到其他点的最短距离数组
	for (int i = 1;i <= n;i++) {
		int j = -1;	//	j存储距离最小点
		for (int k = 1;k <= n;k++) {
			if (!st[k] && (j == -1 || dis[k] < dis[j])) {
				j = k;
			}
		}
		st[j] = true;
		//	更新数据
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

//	输出最短路径
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
		
		//	输入顶点
		cout << "输入顶点:" << endl;
		for (int i = 1;i <= n;i++) {
			char a;
			cin >> a;
			cmap[a] = i;
			imap[i] = a;
		}

		cout << "输入边:" << endl;
		//	输出边
		for (int i = 1;i <= m;i++) {
			char a, b;
			int d;
			cin >> a >> b >> d;
			g[cmap[a]][cmap[b]] = d;
		}
	
		//	输入两个顶点
		cout << "输入起点与终点:" << endl;
		char start, end;
		cin >> start >> end;
		int res = Dijsktra(cmap[start], cmap[end]);
		cout << "res = ";
		cout << res << endl;
		cout << "最短路径:";
		getPath(cmap[end]);
		cout << endl;
	}
	return 0;
}