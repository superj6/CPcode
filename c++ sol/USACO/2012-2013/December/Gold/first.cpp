#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'

const int maxn = 30000, k = 26;
int n;
pair<string, int> s[maxn];
vector<int> g[k];
vector<pair<int, string>> ret;

void dfs(int c, bool (&used)[k]){
	for(int i : g[c]){
		if(!used[i]){
			used[i] = 1;
			dfs(i, used);
		}
	}
}

void recur(int x, int l, int r){
	//cout << l << " " << r << " " << x << endl;
	if(l == r || s[l].first.size() == x){
		ret.push_back({s[l].second, s[l].first});
		return;
	}else if(s[l].first[x] == s[r].first[x]){
		recur(x + 1, l, r);
		return;
	}
	
	bool cur[k], used[k];
	memset(cur, 0, sizeof(cur));
	memset(used, 0, sizeof(used));
	for(int i = l; i <= r; i++){
		cur[s[i].first[x] - 'a'] = 1;
		dfs(s[i].first[x] - 'a', used);
	}
	
	for(int i = l, j = l; i <= r; i++){
		if(i == r || s[i + 1].first[x] != s[i].first[x]){
			int c = s[i].first[x] - 'a';
			if(!used[c]){
				for(int y = 0; y < k; y++){
					if(c != y && cur[y]) g[c].push_back(y);
				}
				recur(x + 1, j, i);
				for(int y = 0; y < k; y++){
					if(c != y && cur[y]) g[c].pop_back();
				}
			}
			j = i + 1;
		}
	}
}

int main() {
	freopen("first.in", "r", stdin);
	freopen("first.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> s[i].first;
		s[i].second = i;
	} 
	
	sort(s, s + n);
	
	recur(0, 0, n - 1);
	
	sort(ret.begin(), ret.end());
	cout << ret.size() << endl;
	for(int i = 0; i < ret.size(); i++) cout << ret[i].second << endl;;
	
	return 0;
}