#include<iostream>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
using namespace std;

const int N = 1e3, vn = 1e5;
// 定义存储结构
int head[N], ne[vn], e[vn], idx;
float res[N];
typedef pair<int, int>layer;
queue<layer>q;
bool st[N];


void init() {
	memset(head, -1, sizeof(head));
	idx = 0;
}

//	插入结点连接的关系
void add(int a, int b) {
	e[idx] = b;
	ne[idx] = head[a];
	head[a] = idx++;
}

void input(int n,int m) {
	init();
	while (m--) {
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
}

void result(int n) {
	for (int i = 1;i <= n;i++) {
		queue<layer>emptyQueue;
		swap(q, emptyQueue);
		memset(st, false, sizeof(st));

		st[i] = true;
		layer l(i, 1);
		q.push(l);
		int count = 0;
		while (!q.empty()) {
			layer ele = q.front();
			q.pop(); 
			//	遍历ele
			int elayer = ele.second;	//	结点的层级
			if (elayer <= 7) {
				count++;
			}
			else {
				break;
			}
			int v = ele.first;
			for (int i = head[v];i != -1;i = ne[i]) {
				int node = e[i];
				if (!st[node]) {
					st[node] = true;
					layer ele(node, elayer + 1);
					q.push(ele);
				}
			}
		}
		res[i] = count * 100 / n;
	}
	for (int i = 1;i <= n;i++) {
		printf("%d:%.2f", i, res[i]);
		cout << "%" << endl;
	}
}

int main() {
	int n, m;
	while (cin >> n >> m && n && m) {
		input(n, m);
		result(n);
	}
	return 0;
}