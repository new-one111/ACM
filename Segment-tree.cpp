#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int a[N];
struct SegmentTree {
	int l, r;
	int dat;
}t[N*4];

void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r; // 节点p代表区间[l, r]
	if(l == r) { t[p].dat = a[l]; return ;} // 叶节点
	int mid = (l + r) >> 1; // 折半
	build(p*2, l, mid); // 左节点 [l, mid], 编号p*2
	build(p*2+1,mid+1, r); // 右节点 [mid + 1,  r] 编号 p*2+1
	t[p].dat = max(t[p*2].dat, t[p*2 + 1].dat); // 从下往上传递信息
}

void change(int p, int x,int v) {
	if(t[p].l == t[p].r) {t[p].dat = v; return ;} // 叶节点
	int mid = (t[p].l + t[p].r) >> 1;
	if(x <= mid) change(p*2, x, v); // x属于左半边
	else change(p*2+1, x, v); // x属于右半边
	t[p].dat = max(t[p*2].dat, t[p*2+1].dat); // 从下往上更新
} // O(log(n))

int ask(int p, int l, int r) {
	if(l <= t[p].l && r >= t[p].r) return t[p].dat; // 完全包含
	int mid = (t[p].l + t[p].r) >> 1;
	int val = -(1<<30); // 负无穷
	if(l <= mid) val = max(val, ask(p*2, l, r)); // 左子叶有重叠
	if(r > mid) val = max(val, ask(p*2+1, l, r)); // 右子叶有重叠
	return val;
}
int main () {
	int n;
	cin >> n;
	for(int i = 1;i <= n;i ++) cin >> a[i];
	// 建树
	build(1, 1, n);
	// 单点修改, 将A[x]的值改为v
	// change(1, x, v);
	// 询问 l, r的最大值
	cout << ask(1, 1, 3) << endl;
	return 0;
}