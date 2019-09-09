#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, k;
	cin >> n >> k;
	
	multiset<int> t;
	pair<int, int> a[n];
	for(int i = 0; i < n; i++) cin >> a[i].second >> a[i].first;
	for(int i = 0; i < k; i++) t.insert(0);
	
	sort(a, a + n);
	int cnt = 0;
	
	for(int i = 0; i < n; i++){
		auto cur = t.lower_bound(-a[i].second);
		
		if(cur == t.end()) continue;
		
		cnt++;
		t.erase(cur);
		t.insert(-a[i].first);
	}
	
	cout << cnt << endl;

	return 0;
}