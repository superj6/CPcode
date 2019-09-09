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
	
	int maxv = 1;
	set<pair<int, int>> last;
	
	while(n-- > 0){
		int c;
		cin >> c;
		
		auto cur = last.upper_bound(make_pair(-c, n + 1));
		
		if(cur == last.end()){
			
			if(last.size() > 0){
				cur--;
				if((*cur).second == 1) last.erase(cur);
			}
			
			last.insert(make_pair(-c, 1));
		}else{
			pair<int, int> p = make_pair(-c, (*cur).second + 1);
			
			if(last.size() > 0 && cur != last.begin()){
				cur--;
				if(p.second >= (*cur).second) last.erase(cur);
			}
			
			last.insert(p);
			maxv = max(maxv, p.second);
		}
	}
	
	cout << maxv << endl;

	return 0;
}