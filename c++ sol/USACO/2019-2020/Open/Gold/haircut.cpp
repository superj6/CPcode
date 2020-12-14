#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 100002;

struct BIT{
	int bit[maxn];
	
	void clr(){
		memset(bit, 0, sizeof(bit));
	}
	
	BIT(){
		clr();
	}
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
	
	int qry(int x){
		int ret = 0;
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

int n;
int a[maxn];
vector<int> v[maxn];
BIT bit;
ll ans[maxn];

int main(){
	freopen("haircut.in", "r", stdin);
	freopen("haircut.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		v[a[i]].push_back(i);
		ans[n + 1] += bit.qry(n) - bit.qry(a[i]);
		bit.add(a[i], 1);
	}
	
	bit.clr();
	for(int i = n; ~i; i--){
		ans[i] = ans[i + 1];
		reverse(v[i].begin(), v[i].end());
		for(int j : v[i]){
			ans[i] -= bit.qry(j);
			bit.add(j, 1);
		}
	}
	
	for(int i = 0; i < n; i++) cout << ans[i] << endl;

	return 0;
}