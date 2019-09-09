#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, x;
	cin >> n >> x;
	
	multiset<int> a;
	for(int i = 0; i < n; i++){
		int l;
		cin >> l;
		a.insert(l);
	}
	
	int cnt = 0;
	
	for(auto it = a.begin(); it != a.end(); it = a.begin(), cnt++){
		int cur = x - *it;
		auto ot = a.upper_bound(cur);
		if(ot != a.begin()) ot = prev(ot);
		
		a.erase(it);
		if(ot != it) a.erase(ot);
	}
	
	cout << cnt << endl;

	return 0;
}