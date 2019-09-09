#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
using namespace std;

int main(){
	ifstream fin ("crowded.in");
	ofstream fout ("crowded.out");

	int n;
	long d;
	fin >> n >> d;
	
	vector<pair<long, long>> cows;
	set<pair<long, long>> tall;
	
	for(int i = 0; i < n; i++){
		long x, h;
		fin >> x >> h;
		cows.push_back(make_pair(h, x));
	}
	
	sort(cows.begin(), cows.end(), greater<pair<long, long>>());
	
	
	int small = 0, large = 0, total = 0;
	
	while(small < n){
		
		if(cows[small].first * 2 <= cows[large].first && large < n){
			tall.insert(make_pair(cows[large].second, cows[large].first));
			large++;
		}else{
			pair<long, long> currcow = make_pair(cows[small].second, cows[small].first);
			
			set<pair<long, long>>::iterator l = --(tall.upper_bound(currcow)), r = tall.upper_bound(currcow);
			if(l != tall.end() && r != tall.end()){
				if((*l).first >= currcow.first - d && (*r).first <= currcow.first + d && (*l).second >= 2 * currcow.second && (*r).second >= 2 * currcow.second){
					total++;
				}
			}
			small++;
		}

	}
	
	fout << total << endl;

	return 0;
}