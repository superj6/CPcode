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
	
	set<pair<int, int>> used;
	int cnt = 0, maxv = 0;
	int a[n];
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		
		auto cur = used.lower_bound(make_pair(a[i], 0));
		
		if(cur != used.end() && (*cur).first == a[i]){
			for(int j = i - cnt; j <= (*cur).second; j++){
				used.erase(make_pair(a[j], j));
				cnt--;
			}
		}
		
		used.insert(make_pair(a[i], i));
		cnt++;
		maxv = max(maxv, cnt);
	}
	
	cout << maxv << endl;

	return 0;
}