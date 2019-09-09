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
	
	set<pair<int, int>> a;
	for(int i = 0; i < n; i++){
		int l;
		cin >> l;
		a.insert(make_pair(l, i + 1));
	}
	
	for(auto it = a.begin(); it != a.end(); it = a.begin()){
		int cur = x - (*it).first;
		auto ot = a.upper_bound(make_pair(cur, 0));

		if(ot == it) ot = next(ot);
		
		if(ot != a.end() && (*ot).first == cur){
			cout << (*it).second << " " << (*ot).second << endl;
			return 0;
		}
		
		a.erase(it);
	}
	
	cout << "IMPOSSIBLE" << endl;

	return 0;
}