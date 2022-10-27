/*
carpet
https://ac.nowcoder.com/acm/contest/27589/E
*/
#include <bits/stdc++.h>
// #define int long long
using namespace std;
using ll = long long;
using umap = unordered_map<int,int>;
using pii = pair<int,int>;
ll gcd(ll x,ll y) {return !y?x:gcd(y,x%y);}

const int N = 1e6+10;
struct KMP {
    int ne[N]; int len;
    char t[N];
    void clear() {
        len = ne[0] = ne[1] = 0;
    }
    // init string T
    void init(char *tt) {
        len = strlen(tt + 1);
        memcpy(t, tt, (len + 2) * sizeof(char));
        ne[1] = 0;
        for(int i = 2, j = 0;i <= len; i ++) {
            while(j > 0 && tt[i] != tt[j + 1]) j = ne[j];
            if(tt[i] == tt[j+1]) j ++;
            ne[i] = j;
        }
    }
    /* 求所有在s串中的start_pos. 如果first_only设置为true，则只返回第一个位置*/
    vector<int> match(char *s, bool first_only) {
        int lens = strlen(s + 1);
        vector<int> start_pos(0);
        for(int i = 1, j = 0; i <= lens; i ++) {
            while(j > 0 && (j == len || s[i] != t[j+1])) j = ne[j];
            if(s[i] == t[j+1]) j ++;
            if(j == len) {
                start_pos.push_back(i - len + 1);
                if(first_only) return start_pos;
                j = ne[j];
            }
        }
        return start_pos;
    }
    /* 循环周期 形如 acaca 中 ac 是一个合法周期 */
    vector<int> periodic() {
        vector<int> ret;
        int  now =  len;
        while(now) {
            now = ne[now];
            ret.push_back(len - now);
        }
        return ret;
    }
    /* 循环节 形如 acac 中ac、acac是循环节，aca不是*/
    vector<int> periodic_loop(){
        vector<int>ret ;
        for (int x : periodic()){
            if (len % x==0)ret.push_back(x);
        }
        return ret;
    }
    int min_periodic_loop(){
        return periodic_loop()[0];
    }
    // border
    void border() {
        for(int i = 1;i <= len;i ++) cout << ne[i] << " ";
        cout << '\n';
    }

} kmper;
vector<string> s;
vector<vector<int>> a;
vector<vector<int>> MaxVal;
char S[N];
int cnt_l[N], cnt_r[N];
int idx[N], hh = 0, tt = -1;
void solve() {
    int n, m;
    cin >> n >> m;
    s.resize(n+1);
    MaxVal.resize(n+1);
    a.resize(n+1);
    for(int i = 1;i <= n; i ++) cin >> s[i];
    for(int i = 1; i <= n;i ++) {
        a[i].resize(m+1);
        MaxVal[i].resize(m+1);
        for(int j = 1;j <= m;j ++) {
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i ++) {
        for(int j = 1;j <= m;j ++) {
            S[j] = s[i][j - 1];
        }
        S[m+1] = '\0';
        kmper.init(S);
        for(auto x : kmper.periodic()) {
            cnt_r[x] ++;
        }
    }
    for(int j = 1;j <= m;j ++) {
        for(int i = 1;i <= n;i ++) {
            S[i] = s[i][j - 1];
        }
        S[n+1] = '\0';
        kmper.init(S);
        for(auto x : kmper.periodic()) {
            cnt_l[x] ++;
        }
    }

    int p, q;
    for(int i = max(n, m) ; i >= 1; i --) {
        if(cnt_r[i] == n) {
            q = i;
        }
        if(cnt_l[i] == m) {
            p = i;
        }
    }
    // cout<< p << " " << q << endl;
    
    for(int i = 1;i <= n;i ++) {
        hh = 0, tt = -1;
        for(int j = 1;j <= m;j ++) {
            while(hh <= tt && j - q + 1 > idx[hh]) hh ++;
            while(hh <= tt && a[i][idx[tt]] <= a[i][j]) tt --;
            idx[++ tt] = j;
            if(j >= q) {
                MaxVal[i][j] = a[i][idx[hh]];
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for(int j = q;j <= m;j ++) {
        hh = 0, tt = -1;
        for(int i = 1;i <= n;i ++) {
            while(hh <= tt && i - p + 1 > idx[hh]) hh ++;
            while(hh <= tt && MaxVal[idx[tt]][j] <= MaxVal[i][j]) tt --;
            idx[++ tt] = i;
            if(i >= p) {
                ans = min(ans, MaxVal[idx[hh]][j]);
            }
        }
    }
    cout << 1ll * (p+1)*(q+1) * ans << endl;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    solve();
    return 0;
}