#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <math.h>
#include <string.h>
using namespace std;
#define endl '\n'

struct suffix{
	int index;
	int sz, type;
	int rank[2];
	
	friend bool operator<(suffix a, suffix b){
		return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1]) : (a.rank[0] < b.rank[0]);
	}
};

int n;
string s;
vector<suffix> suf;
vector<int> lcp[18];
vector<int> amt;

void suffixArray(){
	stable_sort(suf.begin(), suf.end());
	
	int ind[n];
	for(int k = 2; k < n; k += k){
		int rank = 0;
		int prev_rank = suf[0].rank[0];
		suf[0].rank[0] = 0;
		ind[suf[0].index] = 0;
		
		for(int i = 1; i < n; i++){
			if(suf[i].rank[0] != prev_rank || suf[i].rank[1] != suf[i - 1].rank[1]) rank++;
			prev_rank = suf[i].rank[0];
			suf[i].rank[0] = rank;
			ind[suf[i].index] = i;
		}
		
		for(int i = 0; i < n; i++){
			suf[i].rank[1] = k < suf[i].sz ? suf[ind[suf[i].index + k]].rank[0] : -1;
		}
		
		stable_sort(suf.begin(), suf.end());
	}
}

void lcpArray(){
	int rank[n];
	for(int i = 0; i < n; i++){
		rank[suf[i].index] = i;
	}
	for(int i = 0; i < 18; i++) lcp[i].resize(n);
	
	int k = 0;
	for(int i = 0; i < n; i++){
		if(rank[i] == n - 1){
			k = 0;
			continue;
		}
		int j = suf[rank[i] + 1].index;
		while(k < suf[rank[i]].sz  && k < suf[rank[j]].sz && s[i + k] == s[j + k]) k++;
		lcp[0][rank[i]] = k;
		if(k) k--;
	}
	
	for(int i = 1; i < 18; i++){
		for(int j = 0; j + (1 << i) <= n; j++){
			lcp[i][j] = min(lcp[i - 1][j], lcp[i - 1][j + (1 << (i - 1))]);
		}
	}
}

int main(){
	freopen("standingout.in", "r", stdin);
	freopen("standingout.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	int c = n;
	int cow[n];
	
	for(int i = 0; i < n; i++){
		string t;
		cin >> t;
		cow[i] = 0;
		
		for(int j = 0; j < t.size(); j++){
			suffix nx;
			nx.index = s.size() + j;
			nx.sz = t.size() - j, nx.type = i;
			nx.rank[0] = t[j] - 'a', nx.rank[1] = (j + 1 < t.size() ? t[j + 1] - 'a' : -1);
			suf.push_back(nx);
		}
		
		s += t;
	}
	
	n = s.size();
	amt.resize(n);
	suffixArray();
	lcpArray();
	
	int prv = -1;
	for(int i = 1; i < n; i++){
		if(suf[i - 1].type == suf[i].type){
			amt[i] = max(amt[i], lcp[0][i - 1]);
		}else{
			prv = i - 1;
		}
		
		if(prv != -1){
			int j = log2(i - prv);
			amt[i] = max(amt[i], min(lcp[j][prv], lcp[j][i - (1 << j)]));
		}
	}
	prv = -1;
	for(int i = n - 2; i >= 0; i--){
		if(suf[i].type != suf[i + 1].type){
			prv = i + 1;
		}
		
		if(prv != -1){
			int j = log2(prv - i);
			amt[i] = max(amt[i], min(lcp[j][i], lcp[j][prv - (1 << j)]));
		}
	}
	
	for(int i = 0; i < n; i++) cow[suf[i].type] += suf[i].sz - amt[i];
	
	for(int i = 0; i < c; i++) cout << cow[i] << endl;

	return 0;
}