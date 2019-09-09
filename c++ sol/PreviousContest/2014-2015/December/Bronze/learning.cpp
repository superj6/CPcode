#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <math.h>
using namespace std;

struct cow{
	int s, w;
	
	cow(int s, int w){
		this->s = s;
		this->w = w;
	}
	
	friend bool operator<(cow a, cow b){
		return a.w < b.w;
	}
};

int n, a, b;
vector<cow> cows;

int main(){
	ifstream fin ("learning.in");
	ofstream fout ("learning.out");
	
	map<string, int> spots;
	
	spots["S"] = 1;
	spots["NS"] = 0;

	fin >> n >> a >> b;
	
	for(int i = 0; i < n; i++){
		string s;
		int w;
		fin >> s >> w;
		
		cows.push_back(cow(spots.find(s)->second, w));
	}
	
	sort(cows.begin(), cows.end());
	
	int spotted = 0;
	
	int prev = -1;
	
	if(a < cows[0].w && cows[0].s){
		spotted += cows[0].w - a + 1;
		prev = cows[0].w;
		//cout << a << " " << cows[0].w << " " << spotted << endl;

	}
	
	for(int i = 1; i < n; i++){
		int minv = max(cows[i - 1].w, a);
		int maxv = min(cows[i].w, b);
		int curr;
		
		if(minv > maxv) continue;
		
		double middle = (double)(cows[i - 1].w + cows[i].w)/2;
		
		if(cows[i - 1].s && cows[i].s){
			spotted += maxv - minv + 1;
			if(minv == prev) spotted--;
			prev = maxv;
			
			//cout << minv << " " << maxv << " " << spotted << endl;
		}else if(cows[i - 1].s && !cows[i].s){
			if(middle >= minv){
				spotted += min((int)floor(middle), maxv) - minv + 1;
				if(minv == prev) spotted--;
				prev = min((int)floor(middle), maxv);
				
				//cout << minv << " " << min((int)floor(middle), maxv) << " " << spotted << endl;
				
			}

		}else if(!cows[i - 1].s && cows[i].s){
			if(middle <= maxv){
				spotted += maxv - max((int)ceil(middle), minv) + 1;
				if(max((int)ceil(middle), minv) == prev) spotted--;
				prev = maxv;
				//cout << max((int)ceil(middle), minv) << " " << maxv << " " << spotted << endl;

			}
		}
	}
	
	if(b > cows[n - 1].w && cows[n - 1].s){
		spotted += b - cows[n - 1].w + 1;
		if(prev == cows[n - 1].w) spotted--;
		//cout << cows[n - 1].w << " " << b << " " << spotted << endl;

	}
	
	fout << spotted << endl;

	return 0;
}