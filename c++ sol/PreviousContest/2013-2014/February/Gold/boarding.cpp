#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
using namespace std;
#define endl '\n'

const int maxn = 200100;
const int maxh = 22;

int s[maxn];
int t[maxn];

int nxt[maxh + 1][maxn];
int lazy[maxh + 1][maxn];

int a[maxn];
int b[maxn];

int n;
int cur = 0;
int head = 1;

void down(int r, int n){
	if(r == 0) return;
	bool first = true;
	for(int x = n; x != nxt[r][n]; x = nxt[r - 1][x]){
		if(!first) a[x] -= lazy[r][n];
		first = false;
		lazy[r - 1][x] += lazy[r][n];
	}
	lazy[r][n] = 0;
}

int geth(){
	for(int i = 0; i < maxh; i++){
		if(rand() % 2) return i;
	}
	return maxh;
}

bool better(int x, int y){
	return b[x] - a[x] >= b[y] - a[y];
}

int main(){
	freopen("boarding.in", "r", stdin);
	freopen("boarding.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> s[i] >> t[i];
	}
	
	cur++;
	int ans = 0;
	for(int i = n; i >= 1; --i){
		cur++;
		a[cur] = s[i];
		int height = geth();
		
		int x = head;
		for(int r = maxh; r >= 0; r--){
			while(nxt[r][x] && a[nxt[r][x]] < a[cur]) x = nxt[r][x];
			down(r, x);
		}
		
		int val = b[x] - a[x] + s[i] + t[i];
		b[cur] = val;
		if(val > ans) ans = val;
		
		x = head;
		a[x]--;
		for(int r = maxh; r >= 0; r--){
			while(nxt[r][x] && a[nxt[r][x]] < a[cur]){
				lazy[r][x]++;
				x = nxt[r][x];
				a[x]--;
			}
			down(r, x);
			
			while(nxt[r][x] && better(cur, nxt[r][x])){
				down(r, nxt[r][x]);
				nxt[r][x] = nxt[r][nxt[r][x]];
			}
			
			if(height >= r){
				nxt[r][cur] = nxt[r][x];
				nxt[r][x] = cur;
			}
		}
		
		a[cur]--;
	}
	
	cout << ans << endl;

	return 0;
}