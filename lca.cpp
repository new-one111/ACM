// https://www.acwing.com/problem/content/description/1174/
// 树上差分 https://www.luogu.com.cn/problem/P3258 松鼠的新家
#include <bits/stdc++.h>

using namespace std;

const int  N = 500010, M = N * 2;
int depth[N], n, m, fa[N][16];
int q[N];

int h[N], e[M], ne[M], idx;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void bfs(int root) {
    memset(depth, 0x3f, sizeof depth);
    depth[root] = 1,depth[0] = 0;
    int hh = 0, tt = -1;
    q[++ tt] = root;
    while(hh <= tt) {
        int t = q[hh ++];
        for(int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if(depth[j] > depth[t] + 1) {
                depth[j] = depth[t] + 1;
                q[++ tt] = j;
                fa[j][0] = t;
                for(int k = 1;k <= 15;k ++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

bool st[N];
void dfs(int u, int father) {
    depth[u] = depth[father] + 1, st[u] = true, fa[u][0] = father;
    for(int i = 1; i <= 15; k ++) fa[u][k] = fa[fa[u][k - 1]][k - 1];
    for(int i = h[u]; i != -1; i = ne[i]) {
        if(!st[e[i]]) dfs(e[i], u);
    }
}


int lca(int a, int b) {
    if(depth[a] < depth[b]) swap(a, b);
    // make a skip to the same depth of b
    for(int i = 15;i >= 0; i -- ) {
        if(depth[fa[a][i]] >= depth[b]) {
            a = fa[a][i];
        }
    }
    if(a == b) return a;
    for(int i = 15;i >= 0; i --) {
        if(fa[b][i] != fa[a][i]) {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}

// 求dfs求num的前缀和
int num[N];
void calc(int u, int father) {
    for(int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if(j != father) calc(j, u), num[u] += num[j];
    }
}

void solve() {
    cin >> n;
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i ++) cin >> a[i];
    for(int i = 1; i < n; i ++) {
        int a, b; cin >> a >> b;
        add(a, b); add(b, a);
    }
    dfs(1, 0, 1);
    for(int i = 1;i < n; i ++) {
        int u = a[i], v = a[i + 1];
        int t = LCA(u, v);
        num[u] += 1, num[v] += 1;
        num[fa[t][0]] -= 2;
        num[t] -= 1, num[fa[t][0]] += 1;
    }
    calc(1, 0);
    for(int i = 2; i <= n; i ++) num[a[i]] --;
    for(int i = 1;i <= n; i ++) cout << num[i] << '\n'; 
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    solve();
    return 0;
}