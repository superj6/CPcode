#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

int main(){
	ifstream fin ("msched.in");
	ofstream fout ("msched.out");

	int n;
	fin >> n;
	
	pair<int, int> cows[n];
	
	for(int i = 0; i < n; i++){
		fin >> cows[i].second >> cows[i].first;
	}
	
	sort(cows, cows+n, greater<pair<int, int>>());
	multiset<int, greater<int>> milk;
	
	int total = 0, index = 0;
	
	for(int i = cows[0].first; i > 0; i--){
		while(index < n && cows[index].first >= i){
			milk.insert(cows[index].second);
			index++;
		}
		
		if(milk.size() > 0){
			total += *milk.begin();
			milk.erase(milk.begin());
		}
	}
	
	fout << total << endl;

	return 0;
}