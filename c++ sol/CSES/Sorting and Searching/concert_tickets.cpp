#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m;
	cin >> n >> m;
	
	multiset<int> a;
	
	for(int i = 0; i < n; i++){
		int l;
		cin >> l;
		a.insert(l);
	}
	
	for(int i = 0; i < m; i++){
		int l;
		cin >> l;
		
		auto it = a.upper_bound(l);
		if(it == a.begin()){
			cout << -1 << endl;
			continue;
		}
		
		it = prev(it);
		
		cout << *it << endl;
		
		a.erase(it);
	}

	return 0;
}