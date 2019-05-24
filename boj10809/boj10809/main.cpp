#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


void init(int * chk) {
	int i;
	for (i = 0; i < 200; i++) {
		chk[i] = -1;
	}
}
void check(char * inputS, int * chk) {
	int i;
	for (i = 0; inputS[i] != '\0'; i++) {
		if (chk[inputS[i]] == -1) chk[inputS[i]] = i;
	}
}
int main() {
	char inputS[102];
	int chk[200],i;
	
	/* input & init */
	//initialize
	init(chk);
	//Input string
	scanf("%s", inputS);
	
	/* processing */
	//Get alphabet location
	check(inputS,chk);
	
	/* output */
	//Print answer
	for (i = 'a'; i <= 'z'; i++) {
		printf("%d ", chk[i]);
	}

	return 0;
}