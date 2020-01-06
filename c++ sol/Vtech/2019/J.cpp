#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
 
const int maxn = 4000011;
struct BIT{
	long long bit[maxn];
	
	BIT(){
		memset(bit, 0, sizeof(bit));
	}
	
	void add(int x, long long v){
		for(x++; x < maxn; x += x & -x) bit[x] += v;
	}
 
	long long qry(int x){
		long long ret = 0;
		for(x++; x > 0; x -= x & -x) ret += bit[x];
		return ret;
	}
	
	void add(int a, int b, long long v){
		if(b < a || b >= maxn - 1) return;
		add(a, v);
		add(b + 1, -v);
	}
};

int n;
BIT bit;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		
		bit.add(d, d, c);
		if(!b) continue;
		bit.add(d + 1, d + a, b);
		
		long long v = c + a * b;
		bit.add(d + a + 1, d + a + v / b, -b);
		bit.add(d + a + v / b + 1, d + a + v / b + 1, -(v % b));
	}
	
	long long ret = 0;
	for(long long i = 0, j = 0; i < maxn - 1; i++){
		j += bit.qry(i);
		ret = max(ret, j);
		//cout << j << endl;
	}
	
	cout << ret << endl;

	return 0;
}