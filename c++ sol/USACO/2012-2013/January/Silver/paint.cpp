#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
	ifstream fin ("paint.in");
	ofstream fout ("paint.out");

	int n, k;
	
	fin >> n >> k;
	
	vector<pair<int, int>> ends;
	int last = 0, pos = 0;
	
	for(int i = 0; i < n; i++){
		int dist;
		char c;
		fin >> dist >> c;
		int dir = c == 'R'? 1 : -1;
		
		if(dir != last){
			ends.push_back(make_pair(pos, dir * (last == 0 ? 1 : 2)));
		}
		
		pos += dist * dir;
		last = dir;
	}
	
	ends.push_back(make_pair(pos, last * -1));
	
	sort(ends.begin(), ends.end());
	
	int cur = 0, start, amt = 0;
	
	for(int i = 0; i < ends.size(); i++){
		if(cur + ends[i].second >= k && cur < k) start = ends[i].first;
		if(cur + ends[i].second < k && cur >= k) amt += ends[i].first - start;
		cur += ends[i].second;
	}
	
	fout << amt << endl;

	return 0;
}