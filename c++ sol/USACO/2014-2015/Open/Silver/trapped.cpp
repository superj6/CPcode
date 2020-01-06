#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <vector>
using namespace std;

int n, b;
int inf = 1000000007;

int main(){
	ifstream fin ("trapped.in");
	ofstream fout ("trapped.out");

	fin >> n >> b;	

	vector<int> bales;
	unordered_map<int, int> size;
	
	for(int i = 0; i < n; i++){
		int s, p;
		fin >> s >> p;
		bales.push_back(p);
		size[p] = s;
	}
	
	sort(bales.begin(), bales.end());
	
	vector<int>::iterator li = --upper_bound(bales.begin(), bales.end(), b), ri = upper_bound(bales.begin(), bales.end(), b);
	int best = 1000000007;
	int l = li - bales.begin(), r = ri - bales.begin();
	
	int j = r;
	
	for(int i = l; i >= 0; i--){
		if(j == n) break;
		int d = bales[j] - bales[i];
		while(d > size.find(bales[j])->second){
			j++;
			if(j == n) break;
			d = bales[j] - bales[i];
		}
		if(j == n) break;
		
		int s = size.find(bales[i])->second;
		
		if(s >= d){
			best = 0;
			break;
		}
		
		best = min(best, d - s);
	}
	
	j = l;
	
	for(int i = r; i < n; i++){
		if(j == -1) break;
		int d = bales[i] - bales[j];
		while(d > size.find(bales[j])->second){
			j--;
			if(j == -1) break;
			d = bales[i] - bales[j];
		}
		if(j == -1) break;
		
		int s = size.find(bales[i])->second;
		
		if(s >= d){
			best = 0;
			break;
		}
		
		best = min(best, d - s);
	}
	
	if(best == inf) fout << -1 << endl;
	else fout << best << endl;
	
	return 0;
}