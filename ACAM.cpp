#include <bits/stdc++.h>

using namespace std;

const int N = 1000010, M = 26;
struct ACAM {
	int nxt[N][M], fail[N], qrr[N], id[N];
	int root, idx, t;
	int cnt[N];
	ACAM() {
		clear();
	}
	void clear() {
		memset(nxt[0], 0, sizeof nxt[0]);
		root = idx = 0;
	}
	
	int newnode() {
		idx ++;
		memset(nxt[idx], 0, sizeof nxt[idx]);
		return idx; 
	}
	// string version: insert s[x] to trie-tree
	int insert(string s, int x) {
		int now = root;
		for (int i = 0; i < s.size(); i++) {
			int u = s[i] - 'a';
			if (!nxt[now][u]) nxt[now][u] = newnode();
			now = nxt[now][u];
		}
		return id[x] = now;
	}
	// char version
	int insert(char *s, int x) {
		int now = root;
		for (int i = 0; s[i]; i++) {
			int u = s[i] - 'a';
			if(!nxt[now][u]) nxt[now][u] = newnode();
			now = nxt[now][u];
		}
		return id[x] = now;
	}
	// build the acam
	void build() {
		fail[root] = root;
		queue<int> q;
		for (int i = 0; i < M; i++) if (nxt[root][i]) q.push(nxt[root][i]);
		while(q.size()) {
			int u = q.front(); q.pop();
			qrr[t ++] = u;
			for (int i = 0; i < M; i++) {
				if (!nxt[u][i]) {
					nxt[u][i] = nxt[fail[u]][i];
				}
				else {
					int tmp = nxt[u][i];
					fail[tmp] = nxt[fail[u]][i];
					q.push(tmp);
				}
			}
		}
	}
	// string version
	void solve(string s, int m) {
		int now = root;
		for (int i = 0; i < s.size(); i++) {
			now = nxt[now][s[i] - 'a'];
			cnt[now]++;
		}

		for (int i = t - 1; i; i--) {
			cnt[fail[qrr[i]]] += cnt[qrr[i]];
		}

		for (int i = 0; i < m; i++) {
			cout << cnt[id[i]] << '\n';
		}
	}
} sol;

int n;
string s;
void solve () {
	cin >> n;
	for (int i = 0; i < n; i ++) {
		string x; cin >> x;
		sol.insert(x, i);
	}
	sol.build();
	cin >> s;
	sol.solve(s, n);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	solve();
	return 0;
}