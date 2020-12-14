#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100001, k = 26;
int n;
string s;
int it[maxn], l[maxn], p[maxn];
int tr[maxn][k];
vector<int> v[maxn];
string ret;

void solve(int l, int r){
	if(l > r) return;
	int x = *--upper_bound(v[it[l]].begin(), v[it[l]].end(), r);
	ret[l - 1] = '(', ret[x] = ')';
	solve(l + 1, x), solve(x + 2, r);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	n = s.size();
	
	l[0] = -1;
	for(int i = 1, j = 1; i <= n; i++){
		int c = s[i - 1] - 'a';
		if(l[it[i - 1]] == c){
			it[i] = p[it[i - 1]];
		}else{
			if(!tr[it[i - 1]][c]) tr[it[i - 1]][c] = j++;
			p[it[i] = tr[it[i - 1]][c]] = it[i - 1];
			l[it[i]] = c;
		}
		v[it[i]].push_back(i);
	}
	
	if(it[n]){
		cout << -1 << endl;
	}else{
		ret.resize(n);
		solve(1, n);
		cout << ret << endl;
	}

	return 0;
}