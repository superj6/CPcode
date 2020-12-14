#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ext/rope>
#include <vector>
using namespace std;
using namespace __gnu_cxx;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 1000001;
int n, m, k;
int lp[mxn];
vector<int> p;
rope<int> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	
	for(int i = 1; i <= n; i++) v.push_back(i);
	
	for(int i = 2; p.size() < m; i++){
		if(!lp[i]){
			lp[i] = i;
			p.push_back(i);
			
			int x = i % (n - 1), y = v[0];
			if(x) v.erase(0), v.insert(x, y);
			if(x = i / (n - 1) % n) v += v.substr(0, x), v.erase(0, x);
		}
		for(int j = 0; j < p.size() && p[j] <= lp[i] && i * p[j] < mxn; j++){
			lp[i * p[j]] = p[j];
		}
	}
	
	int it = 0;
	while(v[it] != k) it++;
	
	cout << v[(it + 1) % n] << " " << v[(it + n - 1) % n] << endl;

	return 0;
}