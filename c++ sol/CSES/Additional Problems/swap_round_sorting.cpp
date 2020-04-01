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
int n, m;
int a[maxn];
vector<pi> ans[2];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[i]--;
	}
	
	for(int i = 0; i < n; i++){
		vector<int> v(1, i);
		for(int j = a[i]; j != i; j = a[j]) v.push_back(j);
		for(int t = 0; t < 2; t++)
		for(int j = t; 2 * j + !t < v.size(); j++){
			m = max(m, t + 1);
			ans[t].push_back({v[j], v[v.size() - j - !t]});
			swap(a[v[j]], a[v[v.size() - j - !t]]);
		}
	}
	
	cout << m << endl;
	for(int i = 0; i < m; i++){
		cout << ans[i].size() << endl;
		for(pi j : ans[i]) cout << j.f + 1 << " " << j.s + 1 << endl;
	}
 
	return 0;
}