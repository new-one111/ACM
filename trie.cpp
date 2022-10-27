// https://www.acwing.com/problem/content/4607/
#include <bits/stdc++.h>
// #define int long long
using namespace std;
using ll = long long;
using umap = unordered_map<int,int>;
using pii = pair<int,int>;
ll gcd(ll x,ll y) {return !y?x:gcd(y,x%y);}

const int N = 1e6+10;
int son[N][10],cnt[N],idx;

void insert(string str) {
    int p = 0;
    for(int i = 0; i < str.size() ;i ++) {
        int u = (str[i] - '0')&1 ? 1 : 0;
        if(!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
    }
    cnt[p] ++;
}
void Delete(string str) {
    int p = 0;
    for(int i = 0; i < str.size() ;i ++) {
        int u = (str[i] - '0')&1 ? 1 : 0;
        if(!son[p][u]) return ;
        p = son[p][u];
    }
    cnt[p] --;
}

int query(string str) {
    int p = 0;
    for(int i = 0; i < str.size() ;i ++) {
        int u = (str[i] - '0')&1 ? 1 : 0;
        if(!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}

void solve() {
    int n; cin >> n;
    while(n --) {
        string op;
        string str;
        cin >> op >> str;
        while(str.size() < 18) { str = "0" + str; }
        if(op == "+") insert(str);
        if(op == "-") Delete(str);
        if(op == "?") {
            cout << query(str) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}