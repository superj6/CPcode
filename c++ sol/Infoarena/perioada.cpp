#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define ull unsigned ll
#define pi pair<int, int>
#define f first
#define s second

const int ha = 1000696969;
const int mxn = 100001;
int n, q;
ull a[mxn], p[mxn];
vector<int> v[mxn], d[mxn];

ull f(int l, int r){
	return a[r] - p[r - l + 1] * a[l - 1]; 
}

int main(){
	freopen("perioada.in", "r", stdin);
	freopen("perioada.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	p[0] = 1;
	for(int i = 1; i <= n; i++){
		char c;
		cin >> c;
		a[i] = c + ha * a[i - 1];
		p[i] = ha * p[i - 1];
	}
	
	for(int i = 1; i <= n; i++){
		for(int j = 0; j < 2; j++) v[i].push_back(j);
		for(int j = 2 * i; j <= n; j += i){
			d[j].push_back(i);
			v[i].push_back(f(j - i + 1, j) == f(j - 2 * i + 1, j - i) ? 
				v[i].back() : j - i + 1);
		}
	}
	
	cin >> q;
	
	while(q--){
		int l, r, ret = 0;
		cin >> l >> r;
		
		for(int i : d[r - l + 1]){
			int x = r / i;
			ret += (v[i][x] - i < l && (i * x == r || 
				p[i * (x + 1) - r] * f(i * x + 1, r) + 
				f(l, ((l - 1) / i + 1) * i) == f(i * (x - 1) + 1, i * x)));
		} 
		
		cout << ret << endl;
	}

	return 0;
}