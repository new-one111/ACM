#include <bits/stdc++.h>

using namespace std;

// 树状数组维护前缀和
const int N = 1e5 + 10;
int c[N], a[N], n;

int ask(int x) {
	int ans = 0;
	for(; x; x -= (x & -x)) ans += c[x];
	return ans;
}
void add(int x,int y) {
	for(; x <= N ; x += (x & -x)) c[x] += y;
}
int main () {
	cin >> n;
	for(int i = 1;i <= n;i ++) {
		cin >> a[i];
		add(i, a[i]);
	}
	// 单点修改 在 x 处加上 y
	int x, y;
	cin >> x >> y;
	add(x, y);
	// 查询前缀和
	ask(x);
	// 区间和 l ~ r
	int res = ask(r) - ask(l-1);
	return 0;
}