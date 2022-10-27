#include <bits/stdc++.h>
#define sf scanf
#define pf printf
//#define int long long
using namespace std;

const int N = 100010;
int f[N][20], a[N];

int n, q;
void ST() {
    for(int i = 1;i <= n;i ++) f[i][0] = a[i];
    int t = log(n)/log(2)+1;
    for(int j = 1;j < t;j ++)
        for(int i = 1;i <= n - (1<<j)+1; i ++) 
            f[i][j] = max(f[i][j-1], f[i + (1 <<(j -1))][j-1]);
}

int ST_query(int l,int r) {
    int k = log(r - l + 1) / log(2);
    return max(f[l][k], f[r - (1<<k) + 1][k]);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> q;
    for(int i = 1;i <= n;i ++) cin >> a[i];
    ST();
    while(q --) {
        int l, r;
        cin >> l >> r;
        cout << ST_query(l, r) << endl;
    }
    return 0;
}
