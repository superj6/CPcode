#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 500000;
int n;
int a[mxn], b[mxn], par[mxn];
vector<int> v[mxn];
set<int> s;

int fnd(int x){
	return x == par[x] ? x : par[x] = fnd(par[x]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> b[i];
	for(int i = 0; i < n; i++) cin >> a[i];
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		v[--b[i]].push_back(x);
		par[i] = i;
	}
	
	int st = n - 1;
	for(int i = 0; i < n; st--)
	for(int j = v[st].size(); i < n && j; i++, j--){
		int x = fnd(st);
		j += v[fnd((x + 1) % n)].size();
		par[x] = (x + 1) % n;
	}
	st++;
	
	int ret = 0;
	for(int i = 0; i < n; i++){
		int x = (st + i) % n;
		for(int j : v[x]) s.insert(j);
		if(a[x] < *prev(s.end())){
			s.erase(s.lower_bound(a[x]));
			ret++;
		}else{
			s.erase(s.begin());
		}
	}
	
	cout << ret << endl;
	
	return 0;
}