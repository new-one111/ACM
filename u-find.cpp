#include <bits/sdtc++.h>

using namespace std;

const int N = 1e5+10;
// 需离散化的并查集
unordered_ma<int,int> S;
int get(int x) {
	if(S.count(x) == 0) S[x] = idx++;
	return S[x];
}

int p[N];
int find(int x) {
	if(x != p[x]) return p[x] = find(p[x]);
	return p[x];
}

int main() {
	for(int i = 1;i <= n;i ++) p[i] = i;
	// 离散化操作： a = get(a), b = get(b);
	int pa = find(a), pb = find(b);
	// merge操作
	if(pa != pb) p[pa] = pb;
	// find操作
	if(pa == pb) //YES
	else //NO
}

