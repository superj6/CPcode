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

const int mxn = 101;
int n, m;
int a[mxn], f[mxn];
vector<int> v;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m;
	
	a[0] = a[n] = 1;
	for(int i = 0, x; i < m; i++) cin >> x, a[x] = 1;
	
	for(int i = 1; i <= n; i++)
	for(int j = 0; j < i; j++){
		f[i - j] |= a[i] && a[j];
	}
	
	for(int i = 1; i <= n; i++) if(f[i]) v.push_back(i);
	
	cout << v[0];
	for(int i = 1; i < v.size(); i++) cout << " " << v[i];
	cout << endl;
	
	return 0;
}