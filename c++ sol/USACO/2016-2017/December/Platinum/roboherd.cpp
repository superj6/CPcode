#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'

int n, k;
long long base = 0, mx = 0, cnt, sum;
vector<long long> a[100000];
int f[100000];

void solve(int x, long long budget){
	if(cnt == k) return;
	if(x != -1 && budget < a[x][0]){
		x = upper_bound(f, f + x, budget) - f - 1;
	}
	if(x == -1){
		cnt++;
		sum += budget + 1;
		return;
	}
	
	solve(x - 1, budget);
	
	for(int i = 0; i < a[x].size() && a[x][i] <= budget && cnt < k; i++){
		solve(x - 1, budget - a[x][i]);
	}
}

int main(){
	freopen("roboherd.in", "r", stdin);
	freopen("roboherd.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> k;
	
	for(int i = 0; i < n; i++){
		int m;
		cin >> m;
		
		int v[m];
		
		for(int j = 0; j < m; j++){
			cin >> v[j];
		}
		
		sort(v, v + m);
		
		base += v[0];
		mx += v[m - 1];
		
		if(m == 1){
			i--, n--;
			continue;
		} 
		
		for(int j = 1; j < m; j++){
			a[i].push_back(v[j] - v[0]);
		}
	}
	
	sort(a, a + n);
	
	for(int i = 0; i < n; i++) f[i] = a[i][0];
	
	long long l = 0, r = mx;
	
	
	while(l < r){
		long long mid = l + (r - l) / 2;
		cnt = 0;
		solve(n - 1, mid);
		
		if(cnt == k) r = mid;
		else l = mid + 1;
	}
	
	cnt = 0;
	sum = 0;
	if(l > 0) solve(n - 1, l - 1);
	
	cout << k * (base + l) - sum << endl;

	return 0;
}