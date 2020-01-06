#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 100000;
int n, m;
vector<pi> a[maxn];
bool ans[maxn];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		x--, y--;
		a[x].push_back({y, i});
	}
	
	for(int i = 0, l = -1, r = -1; i < n; i++){
		sort(a[i].begin(), a[i].end(), greater<pi>());
		if(l < r){
			if(a[i].size() >= 1){
				l = max(l, a[i][0].first);
			}
			if(a[i].size() >= 2){
				r = max(r, a[i][1].first);
				ans[a[i][1].second] = 1;
			}
		}else{
			if(a[i].size() >= 1){
				r = max(r, a[i][0].first);
				ans[a[i][0].second] = 1;
			}
			if(a[i].size() >= 2){
				l = max(l, a[i][1].first);
			}
		}
		
		if(l < i || r < i){
			cout << "impossible" << endl;
			return 0;
		}
	}
	
	for(int i = 0; i < m; i++) cout << ans[i];
	cout << endl;

	return 0;
}