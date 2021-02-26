#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define pii pair<int, pi>
#define f first
#define s second

const int m = 1000001;
int n;
int par[m], rnk[m];
vector<int> v[m];

int fnd(int x){ return par[x] == x ? x : par[x] = fnd(par[x]);}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		par[i] = i;
		for(int j = 1; j * j <= x; j++) if(!(x % j)){
			v[j].push_back(i);
			if(j * j != x) v[x / j].push_back(i);
		}
	}
	
	ll ret = 0;
	for(int i = m - 1; ~i; i--)
	for(int j = 1; j < v[i].size(); j++){
		int x = fnd(v[i][0]), y = fnd(v[i][j]);
		if(x != y){
			ret += i;
			if(rnk[x] < rnk[y]) swap(x, y);
			rnk[x] += rnk[x] == rnk[y];
			par[y] = x;
		}
	}
	
	cout << ret << endl;
	
	return 0;
}