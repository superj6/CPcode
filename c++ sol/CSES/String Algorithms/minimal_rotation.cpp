#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<int, int>
#define f first
#define s second

struct Suf{
	int ind;
	pi rnk;
	
	friend bool operator <(Suf a, Suf b){
		return a.rnk < b.rnk;
	}
};

const int maxn = 1000000;
int n;
string s;
Suf suf[maxn];

void SA(){
	for(int i = 0; i < n; i++){
		suf[i].ind = i;
		suf[i].rnk.f = s[i] - 'a';
		suf[i].rnk.s = s[(i + 1) % n] - 'a';
	}
	
	stable_sort(suf, suf + n);
	
	for(int k = 2; k < n; k <<= 1){
		int ind[n];
		int r = 0;
		pi pr = suf[0].rnk;
		suf[0].rnk.f = 0;
		ind[suf[0].ind] = 0;
		
		for(int i = 1; i < n; i++){
			if(suf[i].rnk != pr) r++;
			pr = suf[i].rnk;
			suf[i].rnk.f = r;
			ind[suf[i].ind] = i;
		}
		
		for(int i = 0; i < n; i++){
			suf[i].rnk.s = suf[ind[(suf[i].ind + k) % n]].rnk.f;
		}
		
		stable_sort(suf, suf + n);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> s;
	n = s.size();
	
	SA();
	
	cout << (s.substr(suf[0].ind, n - suf[0].ind) + (suf[0].ind ? s.substr(0, suf[0].ind) : "")) << endl;

	return 0;
}