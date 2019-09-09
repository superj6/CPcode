#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct boot{
	int s, d, i;
	
	boot(int s, int d, int i){
		this->s = s;
		this->d = d;
		this->i = i;
	}
	
	friend bool operator<(boot a, boot b){
		return a.s > b.s;
	}
};

struct tile{
	int f, i;
	
	tile(int f, int i){
		this->f = f;
		this->i = i;
	}
	
	friend bool operator<(tile a, tile b){
		return a.f > b.f;
	}
};

int main(){
	ifstream fin ("snowboots.in");
	ofstream fout ("snowboots.out");
	
	int n, b;
	fin >> n >> b;
	
	vector<boot> boots;
	vector<tile> tiles;
	vector<int> prev, next;
	
	for(int i = 0; i < n; i++){
		int f;
		fin >> f;
		
		prev.push_back(i - 1);
		next.push_back(i + 1);
		
		tiles.push_back(tile(f, i));
	}
	
	for(int i = 0; i < b; i++){
		int s, d;
		fin >> s >> d;
		
		boots.push_back(boot(s, d, i));
	}
	
	sort(tiles.begin(), tiles.end());
	sort(boots.begin(), boots.end());
	
	int pb = 0, pt = 0, maxstep = 1;
	int answer[b];
	
	while(pb < b){
		boot B = boots[pb];
		pb++;
		
		while(pt < n){
			tile T = tiles[pt];
			if(T.f <= B.s) break;
			pt++;
			
			next[prev[T.i]] = next[T.i];
			prev[next[T.i]] = prev[T.i];
			
			maxstep = max(maxstep, next[T.i] - prev[T.i]);
		}
		
		answer[B.i] = (B.d >= maxstep);
		
	}

	for(int i = 0; i < b; i++){
		fout << answer[i] << endl;
	}

	return 0;
}