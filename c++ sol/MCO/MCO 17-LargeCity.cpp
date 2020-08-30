/*
  Realize when sweeping left to right, a range of cells is blocked below current one as far as far as the range of cells are blocked
in the column left of it, and are blocked above the current one farther than current block only if the range of cells left of it reach
the top row. Similar idea is case when sweeping top to bottom. Now you can coordinate compress and sweep both directions while holding
ranges blocked in a set of pairs for each row. You can now subtract all ranges from amount of reachable blocks, but use bit and sweep
to find number of intersections between vertical and horizontal lines, and add those back since the intersections will be deleted twice.
However you have to deal with case when a whole row or column becomes blocked, since this could block cells not looked at due to coordinate
compression. To do this, find the first spot where a whole row or column is blocked, subtract all cells outside of there as blocked, than
only deal with the ranges that become before the row and column blocked, subtracting and finding intersections of those.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

const int mxn = 300003;
ll n, m;
int a[mxn][2];
vector<int> it[2];
vector<int> v[2][mxn];
vector<pii> b;

int id(int x, int y){
	return lower_bound(it[x].begin(), it[x].end(), y) - it[x].begin();
}

//range ds
set<pi> s[2][mxn];

void addr(int i, int j, int x, int y){
	auto it = s[i][j].upper_bound({y + 1, 0});
	if(it->s <= y + 1) y = it->f, it = s[i][j].erase(it);
	while((--it)->s >= x) it = s[i][j].erase(it);
	if(it->f >=  x - 1) x = it->s, it = s[i][j].erase(it);
	s[i][j].insert({y, x});
}

pi qryr(int i, int j, int x){
	pi p = *s[i][j].lower_bound({x, 0});
	swap(p.f, p.s);
	return p.f <= x && x <= p.s ? p : (pi){0, 0};
}
//end range ds

//bit
int bit[mxn];

void addb(int x, int v){
	for(x++; x < mxn; x += x & -x) bit[x] += v;
}

int qryb(int x){
	int ret = 0;
	for(x++; x; x -= x & -x) ret += bit[x];
	return ret;
}
//end bit

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> m >> n;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < 2; j++){
		cin >> a[i][j];
		it[j].push_back(a[i][j]);
	}
	
	for(int i = 0; i < 2; i++){
		it[i].push_back(0), it[i].push_back(m);
		sort(it[i].begin(), it[i].end());
		it[i].erase(unique(it[i].begin(), it[i].end()), it[i].end());
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 2; j++) a[i][j] = id(j, a[i][j]);
		for(int j = 0; j < 2; j++) v[j][a[i][j]].push_back(a[i][!j]);
	}
	
	for(int i = 0; i < 2; i++)
	for(int j = 0; j < it[i].size(); j++){
		s[i][j].insert({-1, -1}), s[i][j].insert({m + 2, m + 2});
	}
	
	for(int i = 0; i < 2; i++) addr(i, 0, 1, m);
	
	for(int t = 0; t < 2; t++)
	for(int i = 1; i < it[t].size(); i++){
		sort(v[t][i].begin(), v[t][i].end());
		for(int j : v[t][i]){
			int x = it[t][i], y = it[!t][j], l = 0, r = 0;
			if(it[t][i - 1] == x - 1){
				l = !!~-i * qryr(t, i - 1, y - 1).f, r = qryr(t, i - 1, y + 1).s;
			}
			addr(t, i, !~-l ? l : y, r ? r : y);
		}
	}
	
	ll ret = m * m, x[2];
	for(int i = 0; i < 2; i++){
		x[i] = it[i].size();
		it[i].push_back(m + 1);
	} 
	
	for(int t = 0; t < 2; t++)
	for(int i = 0; i < 2; i++)
	for(int j = 1; j < x[i]; j++)
	for(pi p : s[i][j]){
		if(1 <= p.f && p.f <= m){
			if(t){
				int l = p.s, r = p.f;
				if(l >= it[!i][x[!i]]) continue;
				ret -= min(r, it[!i][x[!i]] - 1) - l + 1;
				r = min(r, it[!i][x[!i] - 1]);
				if(!i) b.push_back({it[0][j], {id(1, l), -id(1, r)}});
				else b.push_back({l, {-j, -j}}), b.push_back({r, {j, j}});
			}else if(p.s == 1 && p.f == m){
				x[i] = j;
				break;
			}
		} 
	}
	
 	for(int i = 0; i < 2; i++) ret -= m * (m - it[i][x[i]] + 1);
	ret += (m - it[0][x[0]] + 1) * (m - it[1][x[1]] + 1);
	
	sort(b.begin(), b.end());
	for(pii i : b){
		if(i.s.f < 0) addb(-i.s.f, 1);
		else if(i.s.s < 0) ret += qryb(-i.s.s) - qryb(i.s.f - 1);
		else addb(i.s.f, -1);
	}
	
	cout << ret << endl;

	return 0;
}
