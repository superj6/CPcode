#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

int main(){
	ifstream fin ("cowrect.in");
	ofstream fout ("cowrect.out");

	int n;
	fin >> n;
	
	pair<int, pair<int, int>> cows[n];
	
	for(int i = 0; i < n; i++){
		char c;
		fin >> cows[i].first >> cows[i].second.second >> c;
		cows[i].second.first = c == 'H' ? 0 : 1;
	}
	
	sort(cows, cows+n);
	
	int maxamt = 0, minarea = 0;
	
	for(int i = 0; i < n; i++){
		set<pair<int, int>> inbound;
		int gabove = 100000, gbelow = -1;
		
		if(!cows[i].second.first){
			for(int j = i; j < n && gabove > cows[i].second.second && gbelow < cows[i].second.second; j++){
				if(!cows[j].second.first){
					if(cows[j].second.second > gbelow && cows[j].second.second < gabove){
						inbound.insert(make_pair(cows[j].second.second, cows[j].first));
					}
				}else{
					if(cows[j].second.second >= cows[i].second.second){
						gabove = min(gabove, cows[j].second.second);
					}
					if(cows[j].second.second <= cows[i].second.second){
						gbelow = max(gbelow, cows[j].second.second);
					}
					
					while(inbound.size() > 0 && (*inbound.begin()).first <= gbelow){
						inbound.erase(inbound.begin());
					}
					
					while(inbound.size() > 0 && (*prev(inbound.end())).first >= gabove){
						inbound.erase(prev(inbound.end()));
					}
				}
				
				if(inbound.size() > 0 && (j == n - 1 || cows[j + 1].first != cows[j].first)){
					int amt = inbound.size();
					int area = (cows[j].first - cows[i].first) * ((*prev(inbound.end())).first - (*inbound.begin()).first);
					
					if(amt > maxamt || (amt == maxamt && area < minarea)){
						maxamt = amt;
						minarea = area;
					}
				}
			}
		}
	}
	
	fout << maxamt << endl << minarea << endl;

	return 0;
}