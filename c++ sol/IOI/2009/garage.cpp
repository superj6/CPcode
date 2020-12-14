#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100, mxm = 2001;
int n, m;
int a[mxn];
int b[mxm], f[mxm];
queue<int> q;
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		pq.push(i);
	} 
	for(int i = 1; i <= m; i++) cin >> b[i];
	
	int ret = 0;
	for(int i = 0; i < 2 * m; i++){
		int x;
		cin >> x;
		if(x > 0) q.push(x);
		else pq.push(f[-x]);
		while(!q.empty() && !pq.empty()){
			int c = q.front(), d = pq.top();
			q.pop(), pq.pop();
			ret += a[d] * b[c];
			f[c] = d;
		}
	}
	
	cout << ret << endl;

	return 0;
}