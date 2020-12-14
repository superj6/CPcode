#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 1000001;

struct BIT{
    int bit[maxn];
    
    BIT(){
        memset(bit, 0, sizeof(bit));
    }
    	
    void add(int x, int v){
        for(; x < maxn; x += x & -x) bit[x] += v;
    }
     
    int qry(int x){
        int ret = 0;
        for(; x; x -= x & -x) ret += bit[x];
        return ret;
    }
};

const int mod = 1000000007;
int n;
int a[maxn];
BIT bit;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	for(int i = 0; i < n; i++) cin >> a[i];
	
	reverse(a, a + n);
	
	int ret = 0;
	for(ll i = 0, j = 0; i < n; i++){
	    (ret += bit.qry(a[i]) * (j + i / 2 + 1) % mod) %= mod;
	    (j += i * (j + i / 2 + 1) % mod) %= mod;
	    bit.add(a[i], 1);
	}

    cout << ret << endl;

	return 0;
}