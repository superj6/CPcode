#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int m = 2000001;
struct BIT{
	long a[m];
	
	BIT(){
		memset(a, 0, sizeof(a));
	}
	
	void add(int x, int v){
		for(x++; x < m; x += x & -x) a[x] += v;
	}
	
	long qry(int x){
		int ret = 0;
		for(x++; x > 0; x -= x & -x) ret += a[x];
		return ret;
	}
	
	long qry(int a, int b){
		return qry(b) - qry(a - 1);
	}
};

struct line{
	int x, y, X, Y;
	
	friend bool operator<(line a, line b){
		return (pi){a.x, -a.X} < (pi){b.x, -b.X};
	}
};

const int maxn = 200000;
int n;
line a[maxn];
BIT bit;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].x >> a[i].y >> a[i].X >> a[i].Y;
		a[i].y += m / 2, a[i].Y += m / 2;
		a[i + n] = {a[i].X, a[i].Y, a[i].x, a[i].y};
	}
	
	sort(a, a + 2 * n);
	
	long ret = 0;
	for(int i = 0; i < 2 * n; i++){
		if(a[i].x < a[i].X){
			bit.add(a[i].y, 1);
		}else if(a[i].x > a[i].X){
			bit.add(a[i].y, -1);
		}else if(a[i].y < a[i].Y){
			ret += bit.qry(a[i].y, a[i].Y);
		}
	}
	
	cout << ret << endl;

	return 0;
}