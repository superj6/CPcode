#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

struct Trie{
	Trie *child[2];
	
	Trie(){
		child[0] = child[1] = NULL;
	}
	
	void add(int x, int i = 30){
		if(i < 0) return;
		int c = (x & (1 << i)) > 0;
		if(!child[c]) child[c] = new Trie();
		child[c]->add(x, i - 1);
	}
	
	int best(int x, int i = 30){
		if(i < 0) return 0;
		int c = (x & (1 << i)) > 0;
		if(child[!c]) return (1 << i) | child[!c]->best(x, i - 1);
		else return child[c]->best(x, i - 1);
	}
} trie;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	int maxv = 0;
	trie.add(0);
	for(int i = 0, cur = 0; i < n; i++){
		int x;
		cin >> x;
		cur ^= x;
		trie.add(cur);
		maxv = max(maxv, trie.best(cur));
	}
	
	cout << maxv << endl;

	return 0;
}