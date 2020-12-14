#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

pi operator+(pi x, pi y){
	return {x.f + y.f, x.s + y.s};
}

pi operator-(pi x, pi y){
	return {x.f - y.f, x.s - y.s};
}

const int mxn = 500, k = 26;
int n, m;
int a[mxn][mxn];
vector<pi> v[k << 1];

void answer(){
	cin >> n >> m;
	
	for(int i = 0; i < 2 * k; i++) v[i].clear();
	for(int i = 0; i < n; i++)
	for(int j = 0; j < m; j++){
		char c;
		cin >> c;
		if(isalpha(c)){
			a[i][j] = 0;
			v[!!isupper(c) * k + tolower(c) - 'a'].push_back({i, j});
		}else{
			a[i][j] = 2 * (c == '-') - 1;
		}
	}
	
	int ret = 0;
	for(int i = 0; i < 2 * k; i++) if(!v[i].empty()){
		pi d = v[i][1] - v[i][0];
		d.f /= max(1, abs(d.f)), d.s /= max(1, abs(d.s));
		if(d.f && d.s){
			cout << "F" << endl;
			return;
		}
		for(pi p = v[i][0] + d; p != v[i][1]; p = p + d){
			int &c = a[p.f][p.s];
			if(!c){
				cout << "F" << endl;
				return;
			}
			ret += !~c == !d.f;
			c = 0;
		}
	}
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}