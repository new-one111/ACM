#include <bits/stdc++.h>
#define fi first
#define se second
#define vec vector
#define P(T) pair<T, T>
#define lp (p<<1)
#define rp (p<<1|1)
#define MP make_pair
#define all(T) T.begin(), T.end()
#define pb push_back 
#define SZ(T) (int)(T.size())
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef double db;
ll random(ll x) { return 1ll * rand() * rand() % x; } // srand((unsigned)(time(0)));

const int N = 200010; 
template<class T>
struct Hash {
	T pw[N], base, mod, hs[N];
	void init(string s, ll Base,ll Mod) {
		pw[0] = 1, base = Base, mod = Mod; 
		for (int i = 1; i <= 200000; i++)
			pw[i] = (pw[i - 1] * base) % mod;
		for (int i = 1; s[i]; i++)
			hs[i] = (hs[i - 1] * base + s[i] - 'a') % mod;
	}
	
	T getH(int l, int r) {
		return (hs[r] - (hs[l - 1] * pw[r - l + 1]) % mod + mod) % mod;
	}
};
Hash<ll> hs1, hs2, hs3, hs4; 

void solve(int CaseT = 1) {
	int n, m;
	cin >> n >> m;
	string a,  b;
	cin >> a >> b;
	a = "#" + a;
	b = "#" + b;
	hs1.init(a, 1331, 998244353);
	hs2.init(b, 1331, 998244353);
	hs3.init(a, 2131, 1000000007);
	hs4.init(b, 2131, 1000000007);
	vec<int> pos;
	for (int i = 1; i + m - 1 <= n; i++) {
		int l = i, r = i + m - 1;
		if (hs1.getH(l, r) == hs2.getH(1, m) && hs3.getH(l, r) == hs4.getH(1, m)) {
			pos.pb(i);
		}
		
	}
	cout << SZ(pos) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int _;
	_ = 1;
//	cin >> _;
	
	for (int i = 1; i <= _; i++) {
		solve(i);
	}
	return 0;
} 
