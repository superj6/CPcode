#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int f = 4;
int n, m, k;
vector<pi> ans;
int s;

void solve(int l, int r){
	s++;
	if(l == r){
		for(int i = 1; i <= f && l * f + i <= n; i++){
			ans.push_back({s, n + l * f + i});
		}
		return;
	}
  	int mid = (l + r) / 2, x = s;
 	s += r - l;
  	solve(l, mid);
  	for(int i = 0; i <= mid - l; i++){
		ans.push_back({x + i, x + r - l + 1 + i});
		ans.push_back({x + i, s + 1 + i % (r - mid)});
	}
  	for(int i = 0; i <= r - mid - 1; i++){
    		ans.push_back({x + mid - l + 1 + i, x + r - l + 1 + i % (mid - l + 1)});
    		ans.push_back({x + mid - l + 1 + i, s + 1 + i});
  	}
  	solve(mid + 1, r);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m >> k;
	
  	s = 2 * n;
	for(int i = 0; i < n; i++){
		ans.push_back({i + 1, s + 1 + i / f});
	}
	
	solve(0, (n - 1) / f);
	
	cout << s << " " << ans.size() << endl;
	for(pi i : ans) cout << i.f << " " << i.s << endl;

	return 0;
} 