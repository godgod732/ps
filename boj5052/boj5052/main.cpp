#include <iostream>
#include <cstring>
using namespace std;

class Trie {
	bool numEnd;
	Trie * next[10];
public:
	//constructor
	Trie(){
		numEnd = false;
		memset(next, 0, sizeof(next));
	}
	//destructor
	~Trie() {
		for (int i = 0; i <= 9; i++) {
			if (next[i])
				delete next[i];
		}
	}
	//insert
	void insert(const char * key) {
		if (*key == '\0') {
			numEnd = true;
		}
		else {
			int curr = *key - '0';
			if (next[curr] == NULL)
				next[curr] = new Trie();
			next[curr]->insert(key + 1);
		}
	}
	//find
	bool find(const char * key) {
		if (*key == '\0')
			return false;
		if (numEnd)
			return true;
		int curr = *key - '0';
		return next[curr]->find(key + 1);
	}
};

char phoneBook[10001][11];
int t, n;
bool result;
int main() {
	Trie * root;
	cin >> t;
	for (int i = 1; i <= t; i++) {
		result = false;
		cin >> n;
		root = new Trie();
		//입력
		for (int i = 1; i <= n; i++) {
			cin >> phoneBook[i];
			
		}
		//처리
		for (int i = 1; i <= n; i++) {
			root->insert(phoneBook[i]);
		}
		for (int i = 1; i <= n; i++) {
			if (root->find(phoneBook[i]))
				result = true;
		}
		//출력
		if (!result) cout << "YES\n";
		else cout << "NO\n";
		delete root;
	}
	return 0;
}