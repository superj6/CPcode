#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int x, n;
	cin >> x >> n;
	
	set<int> pos;
	multiset<int, greater<int>> len;
	
	pos.insert(0);
	pos.insert(x);
	len.insert(x);
	
	for(int i = 0; i < n; i++){
		int a;
		cin >> a;
		
		auto r = pos.upper_bound(a);
		auto l = prev(r);
		
		len.erase(len.find(*r - *l));
		len.insert(*r - a);
		len.insert(a - *l);
		
		pos.insert(a);
		
		cout << *len.begin();
		if(i == n - 1) cout << endl;
		else cout << " ";
	}

	return 0;
}