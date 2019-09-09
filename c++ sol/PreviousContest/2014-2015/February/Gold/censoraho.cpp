#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'

#define L 26

struct trie{
	trie() : ind(-1), fall(NULL){
		memset(next, 0, sizeof(next));
	}
	
	int ind;
	
	trie* fall;
	
	trie* next[L];
	
	trie* step(int ch){
		if(next[ch]){
			return next[ch];
		}else if(fall){
			return next[ch] = fall->step(ch);
		}else{
			return this;
		}
	}
};

int main(){
	freopen("censor.in", "r", stdin);
	freopen("censor.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	string s;
	cin >> s >> n;
	
	vector<string> t(n);
	for(int i = 0; i < n; i++) cin >> t[i];
	
	sort(t.begin(), t.end(), [](const string& x, const string& y) -> bool {
		return x.size() < y.size();
	});
	
	trie* rt = new trie;
	vector<trie*> tnode(n, rt);
	
	int j = 0;
	for(int i = 0; j < t.size(); i++){
		for(int k = j; k < t.size(); k++){
			int ch = t[k][i] - 'a';
			trie* nd = tnode[k];
			if(!nd->next[ch]){
				nd->next[ch] = new trie;
			}
			nd->next[ch]->fall = nd->fall;
			nd = nd->next[ch];
			
			while(nd->fall && !nd->fall->next[ch]){
				nd->fall = nd->fall->fall;
			}
			
			if(nd->fall){
				nd->fall = nd->fall->next[ch];
			}else{
				nd->fall = rt;
			}
			
			tnode[k] = nd;
		}
		
		while(j < t.size() && i + 1 == t[j].size()){
			tnode[j]->ind = j;
			j++;
		}
	}
	
	string r;
	vector<trie*> st(1, rt);
	for(int i = 0; i < s.size(); i++){
		trie* nd = st.back()->step(s[i] - 'a');
		r.push_back(s[i]);
		st.push_back(nd);
		
		if(nd->ind != -1){
			r.resize(r.size() - t[nd->ind].size());
			st.resize(r.size() + 1);
		}
	}
	
	cout << r << endl;
	return 0;
}