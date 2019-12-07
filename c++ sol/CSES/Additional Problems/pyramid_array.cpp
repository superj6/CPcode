#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 200001;
struct BIT{
	int a[maxn];
	
	BIT(){
		memset(a, 0, sizeof(a));
	}
	
	void add(int x, int v){
		for(x++; x < maxn; x += x & -x) a[x] += v;
	}
	
	int qry(int x){
		int ret = 0;
		for(x++; x > 0; x -= x & -x) ret += a[x];
		return ret;
	}
	
	int qry(int a, int b){
		return qry(b) - qry(a - 1);
	}
};

int n;
pi p[maxn];
BIT bit;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> p[i].first;
		p[i].second = i;
	}
	
	sort(p, p + n);
	
	long ret = 0;
	for(int i = 0; i < n; i++){
		int x = p[i].second;
		ret += min(x - bit.qry(0, x), n - x - 1 - bit.qry(x, n - 1));
		bit.add(p[i].second, 1);
	}
	
	cout << ret << endl;

	return 0;
}