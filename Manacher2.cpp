#include<stdio.h>
char qdu[40000050];
int manacher() {
	register int i,res = 0;
	for(i = 1; qdu[i]; ++i) {
		int l(i),r(i);
		while(qdu[i] == qdu[r+1]) ++r;
		i = r;
		while(qdu[l-1] == qdu[r+1]) ++r,--l;
		if(res < r-l+1)	res = r-l+1;
	}
	return res;
}
int main() {
	int loop;
	qdu[0] = '$';
	gets(qdu+1);
	printf("%d\n",manacher());

	return 0;
}