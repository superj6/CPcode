#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define pi pair<int, int>

const int inf = 0x3f3f3f3f;
const int mxn = 1 << 18;

struct MBIT{
	int bit1[2][mxn], bit2[2][mxn];
	
	MBIT(){
		memset(bit1, inf, sizeof(bit1));
		memset(bit2, inf, sizeof(bit2));
	}
	
	void add(int bit[2][mxn], int x, int v){
		int ov = bit[0][x];
		bit[0][x] = v;
		for(; x < mxn; x += x & -x){
			if(v > bit[1][x]){
				if(ov == bit[1][x]){
					v = min(v, bit[0][x]);
					for(int y = (x & -x) >> 1; y; y >>= 1){
						v = min(v, bit[1][x - y]);
					}
				}else break;
			}
			if(v == bit[1][x]) break;
			bit[1][x] = v;
		}
	}
	
	void add(int x, int v){
		x++;
		add(bit1, x, v);
		add(bit2, mxn - x, v);
	}
	
	int qry(int bit[2][mxn], int x, int y){
		int ret = inf;
		for(; x <= y - (y & -y); y -= y & -y){
			ret = min(ret, bit[1][y]);
		}
		ret = min(ret, bit[0][y]);
		return ret;
	}
	
	int qry(int x, int y){
		x++, y++;
		int ret = inf;
		ret = min(ret, qry(bit1, x, y));
		ret = min(ret, qry(bit2, mxn - y, mxn - x));
		return ret;
	}
};

int n, q;
MBIT bit;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> q;
	
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		bit.add(i, x);
	}
	
	for(int i = 0; i < q; i++){
		int t;
		cin >> t;
		if(t == 1){
			int k, x;
			cin >> k >> x;
			k--;
			bit.add(k, x);
		}else{
			int a, b;
			cin >> a >> b;
			a--, b--;
			cout << bit.qry(a, b) << endl;
		}
	}
	
	return 0;
}