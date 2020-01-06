#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
#include <iterator>
using namespace std;
#define endl '\n'

int main(){
	freopen("trapped.in", "r", stdin);
	freopen("trapped.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	pair<int, int> bales[n];
	
	for(int i = 0; i < n; i++){
		cin >> bales[i].second >> bales[i].first;
	}
	
	sort(bales, bales+n);
	
	priority_queue<pair<int, int>> q;
	
	for(int i = 0; i < n; i++){
		q.push(make_pair(bales[i].second, i));
	}
	
	bool works[n];
	for(int i = 0; i < n; i++) works[i] = false;
	set<int> used;
	int area = 0;
	
	while(!q.empty()){
		int cur = q.top().second;
		q.pop();
		
		if(works[cur]) continue;
		
		used.insert(cur);
		
		set<int>::iterator itr = used.lower_bound(cur);
		
		if(next(itr) != used.end()){
			int r = *next(itr);
			
			if(bales[r].first - bales[cur].first <= min(bales[cur].second, bales[r].second)){
				for(int i = cur; i <= r; i++) works[i] = true;
				area += bales[r].first - bales[cur].first;
			}
		}
		
		if(prev(itr) != prev(used.begin())){
			int l = *prev(itr);
			if(bales[cur].first - bales[l].first <= min(bales[cur].second, bales[l].second)){
				for(int i = l; i <= cur; i++) works[i] = true;
				area += bales[cur].first - bales[l].first;
			}
		} 

	}
	
	cout << area << endl;

	return 0;
}