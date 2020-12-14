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
 
const int mxn = 400001;
int n;
int a[mxn], f[mxn], ans[mxn];
 
void add(int x, int v){
	for(; x; x >>= 1){
		if(a[x] == v){
			f[x] = 0;
			break;
		}
		if(x & 1){
			if(a[x ^ 1] == v){
				f[x] = f[x ^ 1] = 1;
				break;
			}
			f[x ^ 1] = 0;
		}
		f[x] = 1;
	}
}
 
int qry(int x){
	int ret = mxn;
	for(; x; x >>= 1){
		if(~-f[x]) ret = min(ret, a[x]);
		if(!f[x]) break;
		if((x & 1) && f[x ^ 1]){
			ret = min(ret, a[x ^ 1]);
			if(!~-f[x ^ 1]) break;
		}
	}
	return ret;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	memset(a, 0x3f, sizeof(a));
	memset(f, -1, sizeof(f));
	for(int i = 1; i <= n; i++) cin >> a[i];
	f[1] = 0;
	
	for(int i = 1; i <= n; i++){
		int x = qry(i), l = i << 1, r = i << 1 | 1;
		ans[i] = min({x, a[l], a[r]});
		if(ans[i] == x) f[l] = f[r] = 0, add(i, x);
		if(ans[i] == a[l]) f[l] = 1, f[r] = 0;
		if(ans[i] == a[r]) f[r] = 1;
	}
	
	cout << ans[1];
	for(int i = 2; i <= n; i++) cout << " " << ans[i];
	cout << endl;
 
	return 0;
}