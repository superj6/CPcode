#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
#define vi vector<int>

const int maxn = 151;
int n;
int a[maxn];
vi graph[maxn];

bool qry(vi &v){
	int k = v.size();
	cout << k;
	for(int i : v) cout << " " << i;
	cout << endl;
	int ret;
	cin >> ret;
	return ret == k - 1;
}

void bs(int x, vi &v){
	int l = 0, r = v.size();
	while(r - l > 1){
		int mid = (l + r) / 2;
		vi q(v.begin() + mid, v.begin() + r);
		q.push_back(x);
		if(qry(q)) l = mid;
		else r = mid;
	}
	graph[v[l]].push_back(x);
}

vi solve(int l, int r){
	if(l == r) return vi(1, l);
	
	int mid = (l + r) / 2;
	vi v1 = solve(l, mid), v2 = solve(mid + 1, r);
	int k1 = v1.size(), k2 = v2.size();
	if(k1 * (1 + __lg(k2)) >  k2 * (1 + __lg(k1))) swap(v1, v2);
	
	vi ret = v2;
	for(int i : v1){
		v2.push_back(i);
		bool t = qry(v2);
		v2.pop_back();
		if(t) bs(i, v2);
		else ret.push_back(i);
	}
	
	return ret;
}

void dfs(int c){
	for(int i : graph[c]){
		a[i] = a[c];
		dfs(i);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	vi v = solve(1, n);
	
	for(int i = 0; i < v.size(); i++){
		a[v[i]] = i + 1;
		dfs(v[i]);
	}
	
	cout << 0;
	for(int i = 1; i <= n; i++) cout << " " << a[i];
	cout << endl;

	return 0;
}