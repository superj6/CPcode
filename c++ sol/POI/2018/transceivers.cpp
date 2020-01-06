#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int maxn = 500001;
 
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
		for(x++; x; x -= x & -x) ret += bit[x];
		return ret;
	}
};

const int f = 99999;
int n, m;
int s[maxn], a[maxn];
//RangeBIT
	BIT b1, b2, b3, b4;
	
	void add(int x, long long v){
		b1.add(x, v);
		b2.add(x, v * (x - 1));
	}
	
	void add(int a, int b, long long v){
		add(a, v);
		add(b + 1, -v);
	}
	
	void add2(int x, long long v){
		b3.add(x, v);
		b4.add(x, v * x * (x - 1) / 2);
		add(x, -v * x);
	}
	
	void add2(int a, int b, long long v){
		add2(a, v);
		add2(b + 1, -v);
		add(b + 1, -v * (b - a + 1));
	}
	
	long long qry(int x){
		return (b1.qry(x) * x - b2.qry(x)) + (b3.qry(x) * x * (x + 1) / 2 - b4.qry(x)); 
	}
	
	long long qry(int a, int b){
		return qry(b) - qry(a - 1);
	}
//

void addbase(int x, int s, int a, long long v){
	int d = s / a;
	add(x - d, x + d, v * s % a);
	add(x + 1, x + d, v * (s - s % a));
	add2(x - d, x, v * a);
	add2(x, x + d, -v * a);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> m;
	
	while(m--){
		char c;
		cin >> c;
		
		if(c == 'P'){
			int x;
			cin >> x;
			x += f;
			cin >> s[x] >> a[x];
			addbase(x, s[x], a[x], 1);
		}
		if(c == 'U'){
			int x;
			cin >> x;
			x += f;
			addbase(x, s[x], a[x], -1);
			s[x] = a[x] = 0;
		}
		if(c == 'Z'){
			int l, r;
			cin >> l >> r;
			l += f, r += f;
			cout << (qry(l, r) / (r - l + 1)) << endl;
		}
		//for(int i = 0; i < n; i++) cout << qry(i + f, i + f) << " ";
		//cout << endl;
	}

	return 0;
}