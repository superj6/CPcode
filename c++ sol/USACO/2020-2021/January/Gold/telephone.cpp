#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <deque>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

const int mxn = 50000, mxk = 50;
int n, k;
int a[mxn];
int g[mxk][mxk];
int d[mxn][mxk][2];
deque<pii> q;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++) cin >> a[i], a[i]--;
	
	for(int i = 0; i < k; i++)
	for(int j = 0; j < k; j++){
		char c;
		cin >> c;
		g[i][j] = c & 1;
	}
	
	memset(d, 0x3f, sizeof(d));
	d[0][a[0]][0] = 0;
	q.push_front({0, {a[0], 0}});
	while(!q.empty()){
		pii c = q.front();
		q.pop_front();
		
		int x = c.f + 1 - 2 * c.s.s, dd = d[c.f][c.s.f][c.s.s];
		if(x >= 0 && x < n && d[x][c.s.f][c.s.s] > dd + 1){
			d[x][c.s.f][c.s.s] = dd + 1;
			q.push_back({x, c.s});
		} 
		
		if(g[c.s.f][a[c.f]]){
			if(c.f == n - 1){
				cout << dd << endl;
				return 0;
			}
			
			for(int j = 0; j < 2; j++) if(d[c.f][a[c.f]][j] > dd){
				d[c.f][a[c.f]][j] = dd;
				q.push_front({c.f, {a[c.f], j}});
			}
		}
	}
	
	cout << -1 << endl;
	
	return 0;
}