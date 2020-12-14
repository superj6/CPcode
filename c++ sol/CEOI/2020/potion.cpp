#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
int n, m, k, q;
int a[mxn];
vector<vector<pi>> s[mxn];
vector<int> v[2];

int id(int x, int y){
	for(int i = 0; i < s[x].size(); i++){
		if(s[x][i].back().s == y) return i;
	}
	return -1;
}

void edg(int x, int y, int z){
	int it = id(x, y);
	if(~it){
		s[x][it].push_back({z, -1});
	}else{
		it = id(x, -1);
		if(~it) s[x][it].push_back({z, y});
		else s[x].push_back(vector<pi>(1, {z, y}));
	}
}

void qry(int x, int y, int z){
	v[z].clear();
	for(int i = 0; i < s[x].size() && s[x][i][0].f <= y; i++){
		int it = (--lower_bound(s[x][i].begin(), s[x][i].end(), (pi){y + 1, -1}))->s;
		if(~it) v[z].push_back(a[it]);
	}
	sort(v[z].begin(), v[z].end());
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m >> q;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 1; i <= m; i++){
		int u, v;#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
int n, m, k, q;
int a[mxn];
vector<vector<pi>> s[mxn];
vector<int> v[2];

int id(int x, int y){
	for(int i = 0; i < s[x].size(); i++){
		if(s[x][i].back().s == y) return i;
	}
	return -1;
}

void edg(int x, int y, int z){
	int it = id(x, y);
	if(~it){
		s[x][it].push_back({z, -1});
	}else{
		it = id(x, -1);
		if(~it) s[x][it].push_back({z, y});
		else s[x].push_back(vector<pi>(1, {z, y}));
	}
}

void qry(int x, int y, int z){
	v[z].clear();
	for(int i = 0; i < s[x].size() && s[x][i][0].f <= y; i++){
		int it = (--lower_bound(s[x][i].begin(), s[x][i].end(), (pi){y + 1, -1}))->s;
		if(~it) v[z].push_back(a[it]);
	}
	sort(v[z].begin(), v[z].end());
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k >> m >> q;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	for(int i = 1; i <= m; i++){
		int u, v;
		cin >> u >> v;
		edg(u, v, i), edg(v, u, i);
	}
	
	while(q--){
		int x, y, z;
		cin >> x >> y >> z;
		
		qry(x, z, 0), qry(y, z, 1);
		
		int ret = 1e9;
		for(int i = 0, j = 0; i < v[0].size() && j < v[1].size(); i++){
			while(j < v[1].size() - 1 && v[1][j + 1] < v[0][i]) j++;
			ret = min(ret, abs(v[0][i] - v[1][j]));
			if(j < v[1].size() - 1) ret = min(ret, abs(v[0][i] - v[1][j + 1]));
		}
		
		cout << ret << endl;
	}

	return 0;
}
		cin >> u >> v;
		edg(u, v, i), edg(v, u, i);
	}
	
	while(q--){
		int x, y, z;
		cin >> x >> y >> z;
		
		qry(x, z, 0), qry(y, z, 1);
		
		int ret = 1e9;
		for(int i = 0, j = 0; i < v[0].size() && j < v[1].size(); i++){
			while(j < v[1].size() - 1 && v[1][j + 1] < v[0][i]) j++;
			ret = min(ret, abs(v[0][i] - v[1][j]));
			if(j < v[1].size() - 1) ret = min(ret, abs(v[0][i] - v[1][j + 1]));
		}
		
		cout << ret << endl;
	}

	return 0;
}