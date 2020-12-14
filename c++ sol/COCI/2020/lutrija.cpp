nclude <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
#define i128 __int128
ll ipow(ll b, ll e, ll mod){
  ll ret = 1;
  for(; e; e >>= 1){
    if(e & 1) ret = (i128)ret * b % mod;
    b = (i128)b * b % mod;
  }
  return ret;
}
 
const int ptst = 12;
int p[ptst] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool ptest(ll x){
  if(x <= 1) return !x;
  for(int i = 0; i < ptst; i++) if(x % p[i] == 0) return x == p[i];
  if(x < p[ptst - 1] * p[ptst - 1]) return 1;
 
  ll y = x - 1, e = __lg(y & -y);
  y >>= e;
  for(int i = 0; i < ptst; i++){
    ll z = ipow(p[i], y, x);
    if(z == 1) continue;
    for(int i = 0; i < e && z != x - 1; i++) z = (i128)z * z % x;
    if(z != x - 1) return 0;
  }
 
  return 1;
}
 
 
ll a, b;
 
ll val(ll x){
    for(int i = -2; i <= 2; i += 2){
        if(ptest(x + i - 2) && ptest(x + i)) return x + i;
    }
    return 0;
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> a >> b;
	
	if(ptest(abs(a - b))){
	    cout << 2 << endl;
	    cout << a << " " << b << endl;
	}else{
	    ll x = val(a), y = val(b);
	    if(!x || !y){
	        cout << -1 << endl;
	    }else{
    	    cout << 1 + (x != a) + (x != 2) + (y != 2) + (y != b) << endl;
    	    cout << a << " ";
    	    if(x != a) cout << x << " ";
    	    if(x != 2) cout << 2 << " ";
    	    if(y != b && y != 2) cout << y << " ";
    	    cout << b << endl;
	    }
	}
 
	return 0;
}