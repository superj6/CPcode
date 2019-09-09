#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct timec{
	int t, y, s;
	
	timec(int t, int y, int s){
		this->t = t;
		this->y = y;
		this->s = s;
	}
	
	friend bool operator<(timec a, timec b){
		return a.t < b.t;
	}
};

int main(){
	ifstream fin ("stampede.in");
	ofstream fout ("stampede.out");

	int n;
	fin >> n;
	
	vector<timec> times;
	map<int, int> height;
	vector<bool> used;
	
	for(int i = 0; i < n; i++){
		int x, y, r;
		fin >> x >> y >> r;
		x *= -1;
		
		times.push_back(timec((x - 1) * r, y, 0));
		times.push_back(timec(x * r, y, 1));
		height[y] = i;
		used.push_back(false);
	}
	
	sort(times.begin(), times.end());

	int last = times[0].t, total = 0;
	set<int> curr;
	curr.insert(times[0].y);

	for(int i = 1; i < times.size(); i++){
		if(times[i].t != last && !curr.empty()){
			int thing = height.find(*curr.begin())->second;
			if(!used[thing]){
				total++;
				used[thing] = true;
			}
		}
		
		if(times[i].s == 0){
			curr.insert(times[i].y);
		}else{
			curr.erase(times[i].y);
		}
		last = times[i].t;
	}
	
	fout << total << endl;

	return 0;
}