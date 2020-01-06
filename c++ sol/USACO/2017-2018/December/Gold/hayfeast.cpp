#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

int main(){
	ifstream fin ("hayfeast.in");
	ofstream fout ("hayfeast.out");
	
	int n;
	long long m;
	fin >> n >> m;
	
	long f[n], s[n];
	
	for(int i = 0; i < n; i++){
		fin >> f[i] >> s[i];
	}
	
	multiset<long long, greater<int>> used;
	
	int p1 = 0, p2 = 0;
	long long mins = 1000000000, flavor = f[0];
	used.insert(s[0]);
	
	while(true){
		if(flavor >= m) mins = min(mins, *used.begin());
		
		if(flavor < m || p1 == p2){
			p1++;
			if(p1 == n) break;
			flavor += f[p1];
			used.insert(s[p1]);
		}else{
			flavor -= f[p2];
			multiset<long long, greater<int>>::iterator itr = used.lower_bound(s[p2]);
			used.erase(itr);
			p2++;
		}
	}
	
	fout << mins << endl;

	return 0;
}