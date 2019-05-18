#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
int n,order[1000001],ts;
long long int ans;
int * a, *b, * segmentTree;
//init func
void init(int n) {
	int size = 1;
	a = new int[n];
	b = new int[n];
	while (size <= n) {
		size *= 2;
	}
	size *= 2;
	segmentTree = new int[size];
	for (int i = 0; i < size; i++) segmentTree[i] = 0;
	ts = size/2;
}
//get order
void getOrder() {
	for (int i = 0; i < n; i++) {
		order[b[i]] = i+1;
	}
	for (int i = 0; i < n; i++) {
		a[i] = order[a[i]];
	}
}
//update tree
void update(int idx) {
	idx = ts + idx - 1;
	while (idx>0) {
		segmentTree[idx] += 1;
		idx /= 2;
	}
}
//get answer
int query(int s) {
	
	s = ts + s - 1;
	int e = ts + n - 1;
	int returnV = 0;
	while (s<=e) {
		if (s % 2 == 1) returnV += segmentTree[s];
		if (e % 2 == 0) returnV += segmentTree[e];
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return returnV;
}
int main() {
	
	/* input & preprocessing*/
	//preprocessing
	scanf("%d", &n);
	init(n);
	//input
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
	}
	//make order array
	getOrder();
	/* processing */
	for (int i = 0; i < n; i++) {
		//update tree
		update(a[i]);
		//get answer from bigger than s
		ans += query(a[i]+1);
	}
	/* output */
	printf("%lld", ans);
	return 0;
}