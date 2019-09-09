#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int mod = 2012;

int main(){
	ifstream fin ("bbreeds.in");
	ofstream fout ("bbreeds.out");
	
	int a[1010];
	int l = a[1] = 1;
	
	for(int ch = fin.get(); l > 0 && ch == '(' || ch == ')'; ch = fin.get()){
		int dir = ch == '(' ? 1 : -1;
		l += dir;
		for(int j = dir < 0 ? 1 : l; j >= 1 && j <= l; j -= dir){
			a[j] += a[j - dir];
			if(a[j] >= mod) a[j] -= mod;
		}
		a[l + 1] = 0;
	}
	
	fout << (l == 1 ? a[1] : 0) << endl;

	return 0;
}