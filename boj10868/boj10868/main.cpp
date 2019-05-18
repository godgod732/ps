#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
//쿼리 구조체
typedef struct _query {
	int from, to;
}query;
query question[100001];
int * segmentTree;
int n, m, ts;
int min(int a, int b) {
	if (a > b) return b;
	else return a;
}
//initialize
void init(int n) {
	int size = 1;
	while (1) {
		if (size >= n) break;
		size *= 2;
	}
	size *= 2;
	ts = size;
	//동적 할당
	segmentTree = new int[size];
	for (int i = 0; i < size; i++) segmentTree[i] = 1e9 + 1;
}
//update
void update(int idx, int value) {
	//최솟값 갱신하기
	while (idx >0) {
		segmentTree[idx] = min(segmentTree[idx], value);
		idx /= 2;
	}
}
//rmq
int rmq(int s, int e) {
	int returnV = 1e9 + 1;
	s = ts / 2 + s - 1;
	e = ts / 2 + e - 1;
	//get answer
	while (s <= e) {
		if (s % 2 == 1) returnV = min(returnV, segmentTree[s]);
		if (e % 2 == 0) returnV = min(returnV, segmentTree[e]);
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return returnV;
}

int main() {
	
	//input
	scanf("%d%d", &n, &m);

	/* input & preprocessing*/
	//init
	init(n);
	//input data
	for (int i = 0; i < n; i++) {
		int idx=(ts/2)+i;
		//input query info 
		scanf("%d", &segmentTree[idx]);
		//update
		update(idx, segmentTree[idx]);
	}
	//get answer
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &question[i].from, &question[i].to);
	}
	/* processing */
	for (int i = 0; i < m; i++) {
		printf("%d\n", rmq(question[i].from, question[i].to));
	}
	return 0;
}