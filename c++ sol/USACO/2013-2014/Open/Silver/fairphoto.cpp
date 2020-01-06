#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

int inf = 1000000001;

int main(){
	ifstream fin ("fairphoto.in");
	ofstream fout ("fairphoto.out");

	int n;
	fin >> n;
	pair<int, char> cows[n];
	int sum[n];
	
	for(int i = 0; i < n; i++){
		fin >> cows[i].first >> cows[i].second;
	}
	
	sort(cows, cows+n);
	
	int p = 0, result = 0;
	vector<pair<int, int>> v[2];
	
	for(int i = 0; i < n; i++){
		if(v[p & 1].empty() || p > v[p & 1].back().first){
			v[p & 1].push_back(make_pair(p, cows[i].first));
		}
		
		p += cows[i].second == 'W' ? -1 : 1;
		
		if(!v[p & 1].empty() && p <= v[p & 1].back().first){
			result = max(result, cows[i].first - lower_bound(v[p & 1].begin(), v[p & 1].end(), make_pair(p, -inf))->second);
		}
	}
	
	fout << result << endl;

	return 0;
}