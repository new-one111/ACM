// https://www.luogu.com.cn/problem/P2574
#include <bits/stdc++.h>
// #define int long long
using namespace std;
using ll = long long;
using umap = unordered_map<int,int>;
using pii = pair<int,int>;
ll gcd(ll x,ll y) {return !y?x:gcd(y,x%y);}

const int N = 2e5 + 10;
int a[N];
char s[N];
struct SegmentTree {
	int l, r;
	int dat, lazy;
    #define l(x) tree[x].l
    #define r(x) tree[x].r
    #define dat(x) tree[x].dat
    // #define sum(x) tree[x].sum
    #define lz(x) tree[x].lazy
}tree[N*4];

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    if(l == r) { dat(p) = (s[l] - '0') ; return ;}
    int mid = l + r >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid + 1, r);
    dat(p) = dat(p<<1) + dat(p<<1|1);
}

void spreed(int p) {
    if(lz(p)) {
        dat(p<<1) = r(p<<1) - l(p<<1) + 1 - dat(p<<1);
        dat(p<<1|1) = r(p<<1|1) - l(p<<1|1) + 1 - dat(p<<1|1);
        lz(p<<1) ^= 1, lz(p<<1|1) ^= 1;
        lz(p) = 0;
    }
}

void change(int p, int l, int r) {
    if(l <= l(p) && r >= r(p)) {
        dat(p) = r(p) - l(p) + 1 - dat(p);
        lz(p) ^= 1;
        return ;
    }
    spreed(p);
    int mid = (l(p) + r(p)) >> 1;
    if(l <= mid) change(p<<1, l, r);
    if(r > mid) change(p<<1|1, l, r);
    dat(p) = dat(p<<1) + dat(p<<1|1);
}

int ask(int p, int l, int r) {
    if(l <= l(p) && r >= r(p)) return dat(p);
    spreed(p);
    int mid = (l(p) + r(p)) >> 1;
    int val = 0;
    if(l <= mid) val += ask(p<<1, l, r);
    if(r > mid) val += ask(p<<1|1, l, r);
    return val;
}

void solve() {
    int n, m;
    cin >> n >> m;
    cin >> s+1;
    build(1, 1, n);
    while(m --) {
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 0) {
            change(1, l, r);
        }
        else {
            cout << ask(1, l, r) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}
