#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

ll n, m, k;
ll fst, fp, st, p;

int qry(ll x){
	int ret;
	cout << "? " << x << endl;
	cin >> ret;
	st = x, p *= -1;
	return ret;
}

void rset(int y, ll f = 1){
	st = fst + fp * (f - 1), p = fp;
	for(ll i = 0, x = n - 1; i < y; i++){
		if((x >> i) & 1){
			st += p * x;
			p *= -1, x ^= 1ll << i;
		}
	}
	qry(st);
	p *= -1;
}

void answer(){
	cin >> m;
	n = m - m % 4, k = __lg(n) + 1;
	
	fst = 1, fp = 1;
	for(ll i = m; i > n; i--){
		fst += fp * (i - 1);
		fp *= -1;
	}
	
	ll ret = 0;
	if(n){
		rset(k);
		for(int i = k - 1, j = 0; ~i; i--){
			ll x = ret | (1ll << i);
			if(x >= n) continue;
			if(!qry(st + p * x)) ret = x;
			else if(!j){
				j = 1;
				ll pn = n;
				n = (n & ~((1ll << i) - 1));
				if(pn != n) rset(i, pn & -pn);
			}
		}
	}else{
		st = fst, p = fp, n++;
		qry(st);
	} 
	
	if(ret == max(0ll, m - m % 4 - 1)) while(n++ < m && !qry(st + p * (ret + 1))) ret++;
	
	cout << "= " << ret + 1 << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}