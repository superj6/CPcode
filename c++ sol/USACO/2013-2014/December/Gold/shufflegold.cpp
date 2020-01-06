#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
	ifstream fin ("shufflegold.in");
	ofstream fout ("shufflegold.out");
	
	int n, m, q;
	fin >> n >> m >> q;
	
	int t = n - m + 1;
	
	int p[m - 1];
	int lastn;
	
	for(int i = 0; i < m; i++){	
		int v;
		fin >> v; v--;
		if(v == 0) lastn = i;
		else p[v - 1] = i;
	}

	int why[m - 1];
	
	for(int i = 0; i < q; i++){
		int c, d = 0;
		fin >> c;
		c--;
		c = (2 * n - c - t - 1) % n;

		for(int j = 0; j < t; j++){
			if(c == n - 1) c = lastn;
			else if(c < m - 1){
				c = p[c];
				if(d != 0 && c == why[0]){
					c = why[(t - j - 1) % d];
					break;
				}
				why[d] = c;
				d++;
			}else{
				int nc = c + min(t - j, n - 1 - c);
				j += min(t - j, n - 1 - c) - 1;
				c = nc;
			}
		}
		
		fout << c + 1 << endl;
	}

	return 0;
}