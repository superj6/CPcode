#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int main() {
	ifstream fin ("measurement.in");
	ofstream fout ("measurement.out");
	
	map<int, int> cow;
	
	int n, g;
	fin >> n >> g;
	int cnt = 0, maxv = g;
	
	vector<int> milk;
	vector<pair<int, pair<int, int>>> log;
	
	for(int i = 0; i < n; i++){
		int day, cownum, change;
		fin >> day >> cownum >> change;
		
		if(!cow.count(cownum)){
			cow[cownum] = cnt;
			cnt++;
		}
		
		int index = cow.find(cownum)->second;
		
		log.push_back(make_pair(day, make_pair(index, change)));
	}
	
	sort(log.begin(), log.end());
	milk.resize(cnt);
	for(int i = 0; i < cnt; i++) milk[i] = g;
	int answer = 0;
	bool maxindex[cnt];
	for(int i = 0; i < cnt; i++) maxindex[i] = true;
	
	for(int i = 0; i < n; i++){
		
		if(i != 0){
			if(log[i].first != log[i - 1].first){
				int newmax = g;
				int newmaxindex[cnt];
				for(int j = 0; j < cnt; j++){
					newmaxindex[j] = false;
					newmax = max(milk[j], newmax);
					//cout << milk[j] << " ";
				}
				
				//cout << endl;
				
				bool diff = false;
				
				for(int j = 0; j < cnt; j++){
					if(milk[j] == newmax) newmaxindex[j] = true;
					if(newmaxindex[j] != maxindex[j]) diff = true;
					maxindex[j] = newmaxindex[j];
				}
				
				if(diff) answer++;
			}
		}
		
		int cownum = log[i].second.first, change = log[i].second.second;
		milk[cownum] += change;
		
		//cout << log[i].first << " " << maxv << " " << answer << endl;
		
	}
	
	int newmax = g;
	int newmaxindex[cnt];
	for(int j = 0; j < cnt; j++){
		newmaxindex[j] = false;
		newmax = max(milk[j], newmax);
		//cout << milk[j] << " ";
	}
		
	//cout << endl;
	
	bool diff = false;
	
	for(int j = 0; j < cnt; j++){
		if(milk[j] == newmax) newmaxindex[j] = true;
		if(newmaxindex[j] != maxindex[j]) diff = true;
		maxindex[j] = newmaxindex[j];
	}
	
	if(diff) answer++;
	
	fout << answer;
	
	return 0;
}