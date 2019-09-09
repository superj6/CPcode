#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <math.h>
using namespace std;

int main(){
	ifstream fin ("slowdown.in");
	ofstream fout ("slowdown.out");
	
	int n;
	fin >> n;
	
	vector<double> time, dist;
	
	for(int i = 0; i < n; i++){
		char c;
		int x;
		fin >> c >> x;
		
		if(c == 'T'){
			time.push_back(x);
		}else{
			dist.push_back(x);
		}
	}
	
	sort(time.begin(), time.end());
	sort(dist.begin(), dist.end());
	
	int it = 0, id = 0;
	double timet = 0, distt = 0, multi = 1;
	
	while(it < time.size() || id < dist.size()){
		if((dist[id] - distt) * multi == (time[it] - timet) && it != time.size() && id != dist.size()){
			timet = time[it], distt = dist[id];
			it++, id++;
			multi += 2;
		}else if(((dist[id] - distt) * multi  < (time[it] - timet) && id != dist.size()) || it == time.size()){
			timet += (dist[id] - distt)* multi, distt = dist[id];
			id++;
			multi += 1;
		}else{
			distt += (time[it] - timet) / multi, timet = time[it];
			it++;
			multi += 1;
		}
		
		//cout << timet << " " << distt << endl; 
	}
	
	timet += (1000 - distt) * multi;
	
	fout << (int)round(timet) << endl;

	return 0;
}