#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;

int n, k;

int geta(pair<int, int> a, pair<int, int> b){
	if(a.first >= b.first + k || b.first >= a.first + k || a.second >= b.second + k || b.second >= a.second + k) return 0;
	
	return (min(a.first, b.first) + k - max(a.first, b.first)) * (min(a.second, b.second) + k - max(a.second, b.second));
}

int main(){
	ifstream fin ("squares.in");
	ofstream fout ("squares.out");
	
	fin >> n >> k;

	pair<int, int> sq[n];
	
	for(int i = 0; i < n; i++){
		fin >> sq[i].first >> sq[i].second;
	}
	
	sort(sq, sq+n);
	
	set<pair<int, int>> inbound;
	int area = 0;
	
	for(int i = 0, j = 0; i < n; i++){
		j = max(j, i);
		while(j < n && sq[j].first < sq[i].first + k){
			inbound.insert(make_pair(sq[j].second, sq[j].first));
			j++;
		}
		
		set<pair<int, int>>::iterator itr;
		
		for(itr = prev(inbound.lower_bound(make_pair(sq[i].second, sq[i].first))); itr != prev(inbound.begin()); itr--){
			pair<int, int> cur = make_pair((*itr).second, (*itr).first);
			int a = geta(sq[i], cur);
			if(a > 0){
				if(area == 0){
					area = a;
				}else{
					fout << -1 << endl;
					return 0;
				}
			}else{
				break;
			}
		}
		
		for(itr = next(inbound.lower_bound(make_pair(sq[i].second, sq[i].first))); itr != inbound.end(); itr++){
			pair<int, int> cur = make_pair((*itr).second, (*itr).first);
			
			int a = geta(sq[i], cur);
			if(a > 0){
				if(area == 0){
					area = a;
				}else{
					fout << -1 << endl;
					return 0;
				}
			}else{
				break;
			}
		}
		
		inbound.erase(make_pair(sq[i].second, sq[i].first));
	}
	
	fout << area << endl;

	return 0;
}