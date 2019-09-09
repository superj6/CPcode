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
	
	pair<pair<int, int>, int> a[n];
	
	for(int i = 0; i < n; i++){
		cin >> a[i].first.second >> a[i].first.first;
		a[i].second = i;
	}
	
	sort(a, a + n);
	
	int ans[n];
	set<pair<int, int>> room;
	
	for(int i = 0; i < n; i++){
		auto cur = room.upper_bound(make_pair(-a[i].first.second, 10000000));
		
		if(cur == room.end()){
			ans[a[i].second] = room.size() + 1;
		}else{
			ans[a[i].second] = (*cur).second;
			room.erase(cur);
		}
		
		room.insert(make_pair(-a[i].first.first, ans[a[i].second]));
	}
	
	cout << room.size() << endl;
	for(int i = 0; i < n; i++){
		cout << ans[i];
		if(i == n - 1) cout << endl;
		else cout << " ";
	}
	
	return 0;
}