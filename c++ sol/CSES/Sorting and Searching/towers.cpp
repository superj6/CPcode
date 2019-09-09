#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define endl '\n'

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	multiset<int> blocks;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		
		auto cur = blocks.upper_bound(x);
		
		if(cur != blocks.end()) blocks.erase(cur);
		
		blocks.insert(x);
	}
	
	cout << blocks.size() << endl;

	return 0;
}