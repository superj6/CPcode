#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

const int mxn = 800, w = 4;
const pi dd[w] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, k;
pi s;
int a[mxn][mxn], b[mxn][mxn], d[mxn][mxn];
vector<pi> v;
queue<pi> q, q2;

bool wrk(pi p){
	return p.f >= 0 && p.s >= 0 && p.f < n && p.s < n && ~a[p.f][p.s] && a[p.f][p.s] != -2;
}

bool sol(int x){
	while(!q.empty()) q.pop();
	while(!q2.empty()) q2.pop();
	memcpy(a, b, sizeof(a));
	
	a[s.f][s.s] = 1;
	d[s.f][s.s] = x * k;
	q.push(s);
	for(pi i : v){
		a[i.f][i.s] = -1;
		d[i.f][i.s] = k;
		q2.push(i);
	}
	
	while(!q.empty()){
		pi c = q.front();
		q.pop();
		if(a[c.f][c.s] == 2) return 1;
		while(!q2.empty()){
			pi c2 = q2.front();
			if(!~a[c.f][c.s] || d[c2.f][c2.s] > d[c.f][c.s]) break;
			q2.pop();
			for(int i = 0; i < w; i++){
				pi p = c2 + dd[i];
				if(wrk(p) && a[p.f][p.s] != 2){
					a[p.f][p.s] = -1;
					d[p.f][p.s] = d[c2.f][c2.s] + k;
					q2.push(p);
				}
			}
		}
		if(!~a[c.f][c.s]) continue;
		
		for(int i = 0; i < w; i++){
			pi p = c + dd[i];
			if(wrk(p) && ~-a[p.f][p.s]){
				a[p.f][p.s] = max(a[p.f][p.s], 1);
				d[p.f][p.s] = d[c.f][c.s] + 1;
				q.push(p);
			}
		}
	}
	
	return 0;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++)
	for(int j = 0; j < n; j++){
		char c;
		cin >> c;
		switch(c){
			case 'M':
				s = {i, j};
				break;
			case 'H':
				v.push_back({i, j});
				break;
			case 'D':
				b[i][j] = 2;
				break;
			case 'T':
				b[i][j] = -2;
				break;
		}
	}
	
	int l = -1, r = mxn * mxn;
	while(r - l > 1){
		int mid = (l + r) / 2;
		if(sol(mid)) l = mid;
		else r = mid;
	}
	
	cout << l << endl;

	return 0;
}