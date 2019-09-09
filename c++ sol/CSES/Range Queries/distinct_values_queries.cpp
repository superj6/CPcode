#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'

const int maxn = 200001;
int n, q;
int a[maxn], bit[maxn];
map<int, int> used;

void add(int x, int v){
	if(!x) return;
	for(; x <= n; x += x & -x) bit[x] += v;
}

int qry(int x){
	int ret = 0;
	for(; x > 0; x -= x & -x) ret += bit[x];
	return ret;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	vector<pair<int, int>> rng[n + 1];
	for(int i = 0; i < q; i++){
		int a, b;
		cin >> a >> b;
		rng[b].push_back({a - 1, i});
	}
	
	int ans[q];
	for(int i = 1; i <= n; i++){
		add(used[a[i]], -1);
		used[a[i]] = i;
		add(i, 1);
		
		for(pair<int, int> p : rng[i]){
			ans[p.second] = qry(i) - qry(p.first);
		}
	}
	
	for(int i = 0; i < q; i++) cout << ans[i] << endl;

	return 0;
}