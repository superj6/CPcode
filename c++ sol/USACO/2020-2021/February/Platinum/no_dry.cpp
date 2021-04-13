#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int mxn = 200001;
int n, q;
int a[mxn], b[mxn], f[mxn];
vector<pi> v[mxn];
stack<int> s;

void add(int x, int y){
	for(; x <= n; x += x & -x) b[x] += y;
}

int qry(int x){
	int ret = 0;
	for(; x; x -= x & -x) ret += b[x];
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> q;
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	for(int i = 0; i < q; i++){
		int x, y;
		cin >> x >> y;
		if(x > y) swap(x, y);
		v[y].push_back({x, i});
	}
	
	s.push(0);
	for(int i = 1; i <= n; i++){
		while(a[s.top()] > a[i]) s.pop();
		if(a[s.top()] == a[i]) add(s.top(), -1), s.pop();
		add(i, 1), s.push(i);
		
		for(pi j : v[i]) f[j.s] = qry(i) - qry(j.f - 1);
	}
	
	for(int i = 0; i < q; i++) cout << f[i] << endl;
	
	return 0;
}