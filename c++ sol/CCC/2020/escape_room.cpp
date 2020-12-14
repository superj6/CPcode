#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 1001, k = maxn * maxn;
int n, m;
int a[maxn][maxn];
bool vis[maxn][maxn];
bool vis2[k];
queue<pi> q;

bool works(pi p){
	return p.f > 0 && p.s > 0 && p.f <= n && p.s <= m;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++)
	for(int j = 1; j <= m; j++){
		cin >> a[i][j];
	}
	
	vis[1][1] = 1;
	q.push({1, 1});
	while(!q.empty()){
		pi p = q.front();
		int c = a[p.f][p.s];
		q.pop();
		
		if(vis2[c]) continue;
		vis2[c] = 1;
		
		for(int i = 1; i * i <= c; i++){
			if(c % i == 0){
				pi pp = {i, c / i};
				for(int t = 0; t < 2; t++){
					if(works(pp) && !vis[pp.f][pp.s]){
						vis[pp.f][pp.s] = 1;
						q.push(pp);
					}
					swap(pp.f, pp.s);
				}
			}
		}
	}
	
	cout << (vis[n][m] ? "yes" : "no") << endl;

	return 0;
}