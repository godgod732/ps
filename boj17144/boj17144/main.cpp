#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
int r, c, t, map[52][52], dustIdx;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
typedef struct _point {
	int r, c;
}point;
typedef struct _dust {
	point p;
	int amount;
}dust;
dust newDust[13000];
point airCleaner[2];
//initialize
void init() {
	for (int i = 0; i < r + 1; i++) {
		map[i][0] = -2;
		map[i][c + 1] = -2;
	}
	for (int i = 0; i < c + 1; i++) {
		map[0][i] = -2;
		map[r + 1][i] = -2;
	}
}
//make dust
void makeDust() {
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (map[i][j] >= 5) {
				int steal = 0;
				for (int k = 0; k < 4; k++) {
					if (map[i + dx[k]][j + dy[k]] >= 0) {
						int amount = map[i][j] / 5;
						steal -= amount;
						newDust[dustIdx].p.r = i + dx[k];
						newDust[dustIdx].p.c = j + dy[k];
						newDust[dustIdx].amount = amount;
						dustIdx++;
					}
				}
				newDust[dustIdx].p.r = i;
				newDust[dustIdx].p.c = j;
				newDust[dustIdx].amount = steal;
				dustIdx++;
			}
		}
	}
	for (int i = 0; i < dustIdx; i++) {
		map[newDust[i].p.r][newDust[i].p.c] += newDust[i].amount;
	}
	dustIdx = 0;
}
//air cleaning
void airCleaning() {
	int i;
	//top cleaning
	// [first r-1][1] to [2][1]
	for (i = airCleaner[0].r - 1; i >= 2; i--) {
		map[i][1] = map[i - 1][1];
	}
	//[1][1] to [1][c-1]
	for (i = 1; i <= c - 1; i++) {
		map[1][i] = map[1][i + 1];
	}
	//[1][c] to [firstR -1][c]
	for (i = 1; i <= airCleaner[0].r - 1; i++) {
		map[i][c] = map[i + 1][c];
	}
	//[firstR][C] to [firstR][firstC+2]
	for (i = c; i >= airCleaner[0].c + 2;i--) {
		map[airCleaner[0].r][i] = map[airCleaner[0].r][i - 1];
	}
	//make zero dust
	map[airCleaner[0].r][2] = 0;

	//bottom cleaning
	//[secondR + 1][1] to [r-1][1]
	for (i = airCleaner[1].r + 1; i <= r-1; i++) {
		map[i][1] = map[i + 1][1];
	}
	//[r][1] to [r][c-1]
	for (i = 1; i <= c - 1; i++) {
		map[r][i] = map[r][i + 1];
	}
	//[r][c] to [secondR+1][c]
	for (i = r; i >= airCleaner[1].r+1;i--) {
		map[i][c] = map[i - 1][c];
	}
	//[secondR][C] to [secondR][secondC +2] 
	for (i = c; i >= airCleaner[1].c + 2; i--) {
		map[airCleaner[1].r][i] = map[airCleaner[1].r][i - 1];
	}
	//make zero dust
	map[airCleaner[1].r][2] = 0;
}
//get answer
int getAnswer() {
	int returnV = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			if (map[i][j] > 0) returnV += map[i][j];
		}
	}
	return returnV;
}
int main() {
	/* input & preprocessing */
	//preprocessing
	scanf("%d%d%d", &r, &c, &t);
	init();
	//input
	int cleanerIdx = 0;
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= c; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == -1) {
				airCleaner[cleanerIdx].r = i;
				airCleaner[cleanerIdx].c = j;
				cleanerIdx++;
			}
		}
	}
	/* processing */
	for (int i = 1; i <= t; i++) {
		makeDust();
		airCleaning();
	}
	/* output */
	printf("%d", getAnswer());
	return 0;
}