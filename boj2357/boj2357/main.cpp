#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
//query struct
typedef struct _query {
	int from, to;
}query;
typedef struct _node {
	int minV, maxV;
	_node() : minV(1e9 + 1), maxV(0) {};
}node;
query question[100001];
node * segmentTree;
int n, m, ts;
int min(int a, int b) {
	if (a > b) return b;
	else return a;
}
int max(int a, int b) {
	if (a > b) return a;
	else return b;
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
	//dynamic arrange
	segmentTree = new node[size];
}
//update
void update(int idx, int value) {
	//update tree value
	while (idx >0) {
		segmentTree[idx].minV = min(segmentTree[idx].minV, value);
		segmentTree[idx].maxV = max(segmentTree[idx].maxV, value);
		idx /= 2;
	}
}
//raq
node raq(int s, int e) {
	node returnV;
	s = ts / 2 + s - 1;
	e = ts / 2 + e - 1;
	//get answer
	while (s <= e) {
		if (s % 2 == 1) {
			returnV.minV = min(returnV.minV, segmentTree[s].minV);
			returnV.maxV = max(returnV.maxV, segmentTree[s].maxV);
		}
		if (e % 2 == 0) {
			returnV.minV = min(returnV.minV, segmentTree[e].minV);
			returnV.maxV = max(returnV.maxV, segmentTree[e].maxV);
		}
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
		int idx = (ts / 2) + i;
		int inputV;
		//input query info 
		scanf("%d", &inputV);
		//update
		update(idx, inputV);
	}
	//get answer
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &question[i].from, &question[i].to);
	}
	/* processing */
	for (int i = 0; i < m; i++) {
		node ans = raq(question[i].from, question[i].to);
		printf("%d %d\n", ans.minV,ans.maxV);
	}
	return 0;
}