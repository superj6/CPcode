#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 100000;
ll n;
int a[2][mxn];
vector<int> v[mxn];
map<int, ll> f;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int t = 0; t < 2; t++)
	for(int i = 0; i < n; i++){
		cin >> a[t][i];
		a[t][i]--;
	}
	
	ll ret = n * (n - 1) / 2;
	for(int t = 0; t < 2; t++){
		f.clear();
		for(int i = 0; i < n; i++) f[a[t][i]]++;
		for(auto i : f) ret -= i.s * (i.s - 1) / 2;
	}
	
	for(int i = 0; i < n; i++) v[a[0][i]].push_back(a[1][i]);
	
	for(int t = 0; t < n; t++){
		f.clear();
		for(int i : v[t]) f[i]++;
		for(auto i : f) ret += i.s * (i.s - 1) / 2;
	}
	
	cout << ret << endl;

	return 0;
}