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
	
	pair<long long, pair<long long, long>> a[n];
	for(int i = 0; i < n; i++) cin >> a[i].second.first >> a[i].first >> a[i].second.second;
	
	sort(a, a + n);
	
	long long maxv = 0;
	set<pair<long long, long long>> last;
	last.insert(make_pair(0, 0));
	
	for(int i = 0; i < n; i++){
		
		auto cur = last.upper_bound(make_pair(-a[i].second.first, 10000000000000007));
		
		pair<long long, long long> p = make_pair(-a[i].first, (*cur).second + a[i].second.second);
		
		cur = last.lower_bound(p);
		
		if((*cur).first != p.first && (*cur).second < p.second){
			if(cur != last.begin()){
				cur--;
				if((*cur).second <= p.second) last.erase(cur);
			}
			
			last.insert(p);
		}
		
		maxv = max(maxv, p.second);
		
	}
	
	cout << maxv << endl;

	return 0;
}