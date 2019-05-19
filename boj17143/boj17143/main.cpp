#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


int rSize, cSize, fishSize,ans,fishIdx;
//fish type
typedef struct _fish {
	int speed, d, size;
}fish;
typedef struct _point {
	int r, c;
}point;
typedef struct _factor {
	point p;
	fish f;
}factor;
factor fishArr[10000];
fish map[101][101];
//nextLoc
factor getNextLoc(factor f) {
	int remainSpeed = f.f.speed;
	int nowD = f.f.d;
	//go to wall
	if (nowD == 1) {
		remainSpeed -= (f.p.r - 1);
		if (remainSpeed < 0) f.p.r -= f.f.speed;
		else{
			if ((remainSpeed / (rSize - 1)) % 2 == 0) {
				f.p.r = 1 + (remainSpeed % (rSize - 1));
				f.f.d = 2;
			}
			else {
				f.p.r = rSize - (remainSpeed % (rSize - 1));
				f.f.d = 1;
			}
		}
	}
	else if (nowD == 2) {
		remainSpeed -= (rSize - f.p.r);
		if (remainSpeed < 0) f.p.r += f.f.speed;
		else{
			if ((remainSpeed / (rSize - 1)) % 2 == 0) {
				f.p.r = rSize - (remainSpeed % (rSize - 1));
				f.f.d = 1;
			}
			else {
				f.p.r = 1 + (remainSpeed % (rSize - 1));
				f.f.d = 2;
			}
		}
	}
	else if (nowD == 3) {
		remainSpeed -= (cSize - f.p.c);
		if (remainSpeed < 0) f.p.c += f.f.speed;
		else{
			if ((remainSpeed / (cSize - 1)) % 2 == 0) {
				f.p.c = cSize - (remainSpeed % (cSize - 1));
				f.f.d = 4;
			}
			else {
				f.p.c = 1 + (remainSpeed % (cSize - 1));
				f.f.d = 3;
			}
		}
	}
	else {
		remainSpeed -= (f.p.c - 1);
		if (remainSpeed < 0) f.p.c -= f.f.speed;
		else{
			if ((remainSpeed / (cSize - 1)) % 2 == 0) {
				f.p.c = 1 + (remainSpeed % (cSize - 1));
				f.f.d = 3;
			}
			else {
				f.p.c = cSize - (remainSpeed % (cSize - 1));
				f.f.d = 4;
			}
		}
	}
	return f;
}
//hunting
void hunting(int c) {
	for (int i = 1; i <= rSize; i++) {
		if (map[i][c].size > 0) {
			ans += map[i][c].size;
			map[i][c].size = 0;
			break;
		}
	}
}
//search
void searchFish() {
	factor f;
	for (int i = 1; i <= rSize; i++) {
		for (int j = 1; j <= cSize; j++) {
			if (map[i][j].size > 0) {
				f.p.r = i;
				f.p.c = j;
				f.f.size = map[i][j].size;
				f.f.d = map[i][j].d;
				f.f.speed = map[i][j].speed;
				fishArr[fishIdx++] = getNextLoc(f);
				map[i][j].size = 0;
			}
		}
	}
}
//moving
void moveFish() {
	for (int i = 0; i < fishIdx; i++) {
		//no fish
		if (fishArr[i].f.size > map[fishArr[i].p.r][fishArr[i].p.c].size) {
			map[fishArr[i].p.r][fishArr[i].p.c] = fishArr[i].f;
		}
	}
	fishIdx = 0;
}

int main() {
	int i,row,col,s,z,d;
	/* input & preprocessing */
	//input
	scanf("%d%d%d", &rSize, &cSize, &fishSize);
	for (int i = 0; i < fishSize; i++) {
		scanf("%d%d%d%d%d", &row, &col,&s,&d,&z);
		map[row][col].speed = s;
		map[row][col].d = d;
		map[row][col].size = z;
	}
	/* processing */
	for (int i = 1; i <= cSize; i++) {
		//hunting
		hunting(i);
		//search fish
		searchFish();
		//move fish
		moveFish();
	}

	/* output */
	//print answer
	printf("%d", ans);
	return 0;
}