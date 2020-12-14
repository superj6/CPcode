#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;
#define endl '\n'
#define ll long long
#define ld long double
#define pi pair<int, int>
#define f first
#define s second

const int inf = 0x3f3f3f3f;
const int maxn = 1 << 12;
 
struct MBIT{
	int bit1[2][maxn], bit2[2][maxn];
	 
	void BIT(){
		memset(bit1, inf, sizeof(bit1));
		memset(bit2, inf, sizeof(bit2));
	}
	 
	void add(int bit[2][maxn], int x, int v){
		int ov = bit[0][x];
		bit[0][x] = v;
		for(; x < maxn; x += x & -x){
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
		add(bit2, maxn - x, v);
	}
	 
	int qry(int bit[2][maxn], int x, int y){
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
		ret = min(ret, qry(bit2, maxn - y, maxn - x));
		return ret;
	}
};

int n, m;
ld k;
pi a[maxn];
int dp[maxn];
MBIT bit;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> m >> k;
	k = 1 / k;
	
	for(int i = 0; i < n; i++){
		cin >> a[i].s >> a[i].f;
	}
	
	sort(a, a + n);
	
	memset(dp, inf, sizeof(dp));
	dp[a[0].s] = 0;
	for(int i = 1; i < n; i++){
		for(int j = 0; j < m; j++){
			bit.add(j, dp[j]);
			dp[j] = inf;
		} 
		for(int j = 0; j < m; j++){
			int d = floor(k * (a[i].f - a[i - 1].f));
			dp[j] = bit.qry(max(0, j - d), min(m - 1, j + d)) + abs(a[i].s - j);
		}
	}
	
	cout << dp[a[n - 1].s] << endl;

	return 0;
}