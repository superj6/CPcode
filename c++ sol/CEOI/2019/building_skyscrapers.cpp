#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

struct pt{
	int x, y;
	
	friend pt operator+(pt a, pt b){
		return {a.x + b.x, a.y + b.y};
	}
	
	friend bool operator<(pt a, pt b){
		return a.x != b.x ? a.x < b.x : a.y < b.y;
	}
};

const int maxn = 150000;
int n, k;
pt a[maxn];
map<pt, int> p, s;
set<int, greater<int>> pq;
pt d[8] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
int m = 1;

void dfs(pt c){
 	if(!p.count(c) || !s[c]) return;
	s[c] = 0;
	for(int i = 0; i < 8; i++) dfs(c + d[i]);
}

void dfs2(pt c){
	if(m == 1 && p.count(c)) pq.insert(p[c]);
	if(!s.count(c) || !s[c] || s[c] == m) return;
 	s[c] = m;
	for(int i = 0; i < 4; i++){
		dfs2(c + d[i]);
	} 
}

bool works(pt c){
	set<int> v;
	for(int st = 0; st < 4; st++){
		if(!s[c + d[st]] || !s[c + d[st + 4]]){
			st++;
			for(int i = 0, j = 1; i < 4; i++){
				int l = s[c + d[(st + i) % 4]];
				if(j && l){
					if(v.count(l)) return 0;
					v.insert(l);
					j = 0;
				}
				j |= (!l || !s[c + d[(st + i) % 4 + 4]]);
			}
			break;
		}
	}
	p.erase(c);
	s[c] = -1;
	dfs2(c);
	for(int i = 4; i < 8; i++){
		if(!s[c + d[i]]){
			for(int j = 0; j < 4; j++){
				if(s[c + d[i] + d[j]] == 1){
					pq.insert(p[c + d[i]]);
					break;
				}
			}
		}
	}
	
	return 1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].x >> a[i].y;
		p[a[i]] = i;
		s[a[i]] = -1;
		for(int j = 0; j < 8; j++) s[a[i] + d[j]]= -1;
	}
	
	dfs(a[0]);
	
	for(int i = 1; i < n; i++){
		if(s[a[i]] == -1){
			cout << "NO" << endl;
			return 0;
		}
	}
	
	for(auto i : s){
		if(i.s == -1){
			dfs2(i.f);
			m++;
		}
	}
	
	m = 1;
	vector<int> ans;
	while(!pq.empty()){
		int c = *pq.begin();
		pq.erase(pq.begin());
		if(works(a[c])) ans.push_back(c + 1);
	}
	reverse(ans.begin(), ans.end());
	
	cout << "YES" << endl;
	for(int i : ans) cout << i << endl;

	return 0;
}