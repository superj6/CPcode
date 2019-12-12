#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 200001, mod = 1000000007;
struct BIT{
	long long a[maxn];
	
	BIT(){
		memset(a, 0, sizeof(a));
	}
	
	void add(int x, long long v){
		for(x++; x < maxn; x += x & -x) a[x] = (a[x] + v) % mod;
	}
	
	long long qry(int x){
		long long ret = 0;
		for(x++; x > 0; x -= x & -x) ret = (ret + a[x]) % mod;
		return ret;
	}
};

int n;
int a[maxn];
pi p[maxn];
BIT bit;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i];
		p[i] = {a[i], i};
	}
	
	sort(p, p + n);
	
	for(int i = 0, c = 0; i < n; i++){
		if(i && p[i].first != p[i - 1].first) c++;
		a[p[i].second] = c;
	}
	
	for(int i = 0; i < n; i++){
		bit.add(a[i], bit.qry(a[i] - 1) + 1);
	}
	
	cout << bit.qry(n) << endl;
	
	return 0;
}