#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

int main(){
	ifstream fin ("cowjog.in");
	ofstream fout ("cowjog.out");
	
	int n, t;
	fin >> n >> t;
	
	multiset<long long> ends;
	
	for(int i = 0; i < n; i++){
		long long p, s;
		fin >> p >> s;
		long long curr = -(p + t * s);
		
		if(ends.empty() || curr >= *--ends.end()){
			ends.insert(curr);
		}else{
			ends.erase(ends.upper_bound(curr));
			ends.insert(curr);
		}
	}
	
	fout << ends.size() << endl;

	return 0;
}