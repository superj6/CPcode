#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 200000;
int n;
pi a[maxn];
vector<int> ans;

vector<int> find_subset(int l, int r, vector<int> v){
	n = v.size();
	for(int i = 0; i < n; i++) a[i] = {v[i], i};
	sort(a, a + n);
	
	for(long long i = 0, j = 0, s = 0; i < n; i++){
		s += a[i].f;
		while(j < i && s > r) s -= a[j++].f;
		if(l <= s && s <= r){
			for(int k = j; k <= i; k++) ans.push_back(a[k].s);
			return ans;
		}
	}
	
	return {};
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, l, r;
	cin >> n >> l >> r;
	vector<int> v(n);
	for(int i = 0; i < n; i++) cin >> v[i];
	
	vector<int> ans = find_subset(l, r, v);
	if(!ans.empty()) cout << ans[0];
	for(int i = 1; i < ans.size(); i++) cout << " " << ans[i];
	cout << endl;

	return 0;
}